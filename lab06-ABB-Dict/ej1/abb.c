#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"

//#define INT_MAX +2147483647
//#define INT_MIN -2147483647

struct _s_abb {
    abb_elem elem;          //cabeza
    struct _s_abb *left;    //punteros left
    struct _s_abb *right;   //punteros right
};

static bool elem_eq(abb_elem a, abb_elem b) {
    return a == b;
}

static bool elem_less(abb_elem a, abb_elem b) {
    return a < b;
}
/*
static bool is_abb(abb tree, abb_elem min, abb_elem max){
    bool b = true;
    if (tree != NULL){
        if(elem_less(tree->elem, min) || elem_less(max, tree->elem)){
            b = false;
        }
        else{
            b = is_abb(tree->left, min, tree->elem) && is_abb(tree->right, tree->elem, max);
        }
    }
    return b;
}


static abb_elem getMin(abb tree){
    abb_elem min;
    abb p = tree;
    while(p->left != NULL){
        p = p->left;
    }
    min = p->elem;
    return min;
}

static abb_elem getMax(abb tree){
    abb_elem max;
    abb p = tree;
    while(p->right != NULL){
        p = p->right;
    }
    max = p->elem;
    return max;
}

static bool invrep(abb tree){
    bool b = true;
    if(tree != NULL){
        abb_elem min = getMin(tree);
        abb_elem max = getMax(tree);
        b = is_abb(tree, min, max);
    }
    return b;
}
*/

static bool invrep(abb tree) {
    bool res = true;

    if (tree == NULL){
      res = true;
    } else if (tree->left != NULL && abb_max(tree->left) > tree->elem){
      res = false;
    } else if (tree->right != NULL && abb_min(tree->right) < tree->elem){
      res = false;
    } else if (!invrep(tree->left) || !invrep(tree->right)){
      res = false;
    }

    return res;
}


abb abb_empty(void) {
    abb tree = NULL;
    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));
    if (tree == NULL){
      tree = malloc(sizeof(struct _s_abb));
      tree->elem = e;
      tree->left = NULL;
      tree->right = NULL;
      } else if (elem_less(e, tree->elem)){
      tree->left = abb_add(tree->left, e);
      } else if (e > tree->elem){
      tree->right = abb_add(tree->right, e);
      }
      
    assert(invrep(tree) && abb_exists(tree, e));
    return tree;
}

bool abb_is_empty(abb tree) {
    assert(invrep(tree));
    return tree==NULL;
}

bool abb_exists(abb tree, abb_elem e) {
    assert(invrep(tree));
    bool exists = false;
    if (tree != NULL){
      if (elem_eq(tree->elem,e)){
        exists = true;
      } else if (elem_less(tree->elem,e)){
        exists = exists || abb_exists(tree->right,e);
      } else if (elem_less(e, tree->elem)){
        exists = exists || abb_exists(tree->left,e);
      }
    }

    return exists;
}

unsigned int abb_length(abb tree) {
    unsigned int length=0u;
    assert(invrep(tree));
    if (tree != NULL){
      length = 1u + abb_length(tree->left) + abb_length(tree->right);
    }

    assert(invrep(tree) && (abb_is_empty(tree) ||  length > 0));
    return length;
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree));
    if (tree != NULL){
      if (e < tree->elem){
        tree->left = abb_remove(tree->left, e);
      } else {
        if (e > tree->elem){
          tree->right = abb_remove(tree->right, e);
        } else {
          if (tree->elem == e){
            if (tree->right == NULL && tree->left == NULL){
              free(tree);
              tree = NULL;
            } else {
              if (tree->left == NULL){
                abb tmp = tree;
                tree = tree->right;
                free(tmp);
              } else {
                if (tree->right == NULL){
                  abb tmp = tree;
                  tree = tree->left;
                  free(tmp);
                } else {
                  abb_elem min = abb_min(tree->right);
                  tree->elem = min;
                  tree->right = abb_remove(tree->right, min);
                }
              }
            }
          }
        }
      }
    }

    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}

/*
abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree));
    abb res, hijo;
    abb aux_tree = tree;

    if (tree == NULL){
      res = tree;
    } else if (e < tree->elem){
      tree->left = abb_remove(tree->left, e);
      res = tree;
    } else if (e > tree->elem){
      tree->right = abb_remove(tree->right, e);
      res = tree;
    } else if (tree->left && tree->right){
      aux_tree = encontrar_min(tree->right);
      tree->elem = aux_tree->elem;
      tree->right = abb_remove(tree->right, tree->elem);
      res = tree;
    } else {
      aux_tree = tree;
      if (tree->left == NULL){
        hijo = tree->right;
      }
      if (tree->right == NULL){
        hijo = tree->left;
      }
      res = hijo;
      free(aux_tree);
      aux_tree = NULL;

    }

    assert(invrep(tree) && !abb_exists(tree, e));
    return res;
}*/

abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
      root = tree->elem;

    assert(abb_exists(tree, root));
    return root;
}
/*
abb_elem abb_max(abb tree) {
    assert(invrep(tree) && !abb_is_empty(tree));
    abb_elem max_e;
    if (tree != NULL){
      if (tree->right == NULL){
        max_e = tree->elem;
      } else {
        max_e = abb_max(tree->right);
      }
    }

    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}*/

abb_elem abb_max(abb tree) {
    assert(invrep(tree) && !abb_is_empty(tree));
    abb_elem max_e;
    abb tree_rgt = tree->right;
    if (tree_rgt == NULL){
      max_e = tree->elem;
    } else {
      max_e = abb_max(tree_rgt);
    }

    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    assert(invrep(tree) && !abb_is_empty(tree));
    abb_elem min_e;
    abb tree_lft = tree->left;
    if (tree_lft == NULL){
      min_e = tree->elem;
    } else {
      min_e = abb_min(tree_lft);
    }

    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree) {
    assert(invrep(tree));
    if (tree != NULL) {
        printf("%d ", tree->elem);
        abb_dump(tree->left);
        abb_dump(tree->right);
    }
}

abb abb_destroy(abb tree) {
    assert(invrep(tree));
    if (tree != NULL){
        abb_destroy(tree->left);
        abb_destroy(tree->right);
        free(tree);
        tree = NULL;
    }

    assert(tree == NULL);
    return tree;
}
