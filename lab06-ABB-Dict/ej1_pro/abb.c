#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"
#include "cursor.h"

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
static abb encontrar_min(abb tree){
    if (tree == NULL){
      fprintf(stderr, "Arbol vacio\n");
      return NULL;
    }
    if (tree->left == NULL){
      return tree;
    }
    return encontrar_min(tree->left);
}*/
/*
static bool invrep(abb tree, INT_MIN, INT_MAX){
    if (tree == NULL){
      return true;
    } else if (tree->elem < min || tree->elem > max){
      return false;
    }
    return invrep(tree->left, min, tree->elem-1) && invrep(tree->right, tree->elem+1, max);
}*/

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

static unsigned int max(unsigned int x, unsigned int y) {
    return (x > y ? x: y);
}

// Needed for dumping algorithm
static unsigned int abb_height(abb tree) {
    unsigned int height=0;
    if (tree != NULL) {
        unsigned int left_height=abb_height(tree->left);
        unsigned int right_height=abb_height(tree->right);
        height = 1 + max(left_height, right_height);
    }
    return height;
}

// Calculates branch length in the screen (how many dots) for node
static unsigned int branch_length(abb tree) {
    // 2 ^ (height + 1)
    return (1 << (abb_height(tree) + 1));
}

// Draws right branch
static void branch_right(int n) {
    assert(n > 0);
    cursor_down(1);
    if (n == 1) {
            printf(".");
    } else {
        printf(":");
        for (int i=1; i < n; i++)
            printf(".");
    }
}

// Draws left branch
static void branch_left(int n) {
    assert(n > 0);
    cursor_down(1);
    if (n == 1) {
        printf(".");
        cursor_left(2);
    } else {
        printf(":");
        cursor_left(2);
        for (int i=1; i < n; i++) {
            printf(".");
            cursor_left(2);
        }
    }
}

// Scroll down and makes room for n-lines
static void trunk(int n) {
    for (int i=0;i < n; i++)
        printf("\n");
    cursor_up(n);
}


// Calculates left indentation for tree in the screen
static unsigned dump_left_margin(abb tree) {
    unsigned int margin=1;
    if (tree != NULL) {
        unsigned int length = branch_length(tree->left);
        margin = length + dump_left_margin(tree->left);
    }
    return margin;
}

// Show element (leave cursor in original position after printing)
static void dump_elem(abb tree) {
    assert(tree != NULL);
    int moved=0;  // Holds how many chars where printed
    cursor_white();
    printf("%d%n", tree->elem, &moved);
    // Restore cursor position
    cursor_left(moved);
}

// Dump a tree from an internal node
static void dump(abb tree) {
    cursor_down(1);
    if (tree != NULL) {
        unsigned int length_right = branch_length(tree->right);
        unsigned int length_left = branch_length(tree->left);
        // Print current element
        dump_elem(tree);
        //
        // Print branches
        //
        cursor_green();
        // Print branch left
        branch_left(length_left);
        dump(tree->left);
        cursor_right(length_left);
        // Print branch right
        branch_right(length_right);
        dump(tree->right);
        cursor_left(length_right);
    }
    // Move 2 lines up
    cursor_up(2);
}

// Dump entire tree from the root
void abb_dump(abb tree) {
    assert(invrep(tree));
    unsigned int height=abb_height(tree)+1;
    // Make room for tree in the screen
    trunk(height*2);
    // Place cursor in the root position
    cursor_right(dump_left_margin(tree));
    // Print branches
    dump(tree);
    // Leave cursor after tree
    cursor_down(height*2);
    printf("\r");
    // Restore default color
    cursor_no_color();
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
