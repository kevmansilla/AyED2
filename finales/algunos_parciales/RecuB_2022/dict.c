#include <assert.h>
#include <stdlib.h>
#include "dict.h"
#include "string.h"

struct _dict_t {
  unsigned int size;
  node_t word;
  node_t def;
};

struct _node_t {
  string cadena;
  node_t next;
};

static bool invrep(dict_t d) {
  bool status = false;
  
  //Chequeo de estructura
  assert(d != NULL);
  
  unsigned int len = d->size;
  node_t word,def;
  word = d->word;
  def = d->def;

  //Si tiene size dif a cero no puede no terner elementos 
  if ((len != 0) == (word != NULL && def != NULL)){
    status = true;
  }


  //Cantidad correcta y balanceado
  if (d->word != NULL && d->def != NULL){
    node_t w_word,w_def;
    unsigned int cont = 1u;
    unsigned int z = 0u;

    w_word = d->word; // apunto al primer nodo de word
    w_def = d->def; // apunto al primer nodo de def

    
    while(w_word == NULL){
      assert(w_word != NULL && w_def != NULL); //Me asegura que hay una def por cada palabra
      z = z + 1; //contador de palabras/def
      w_word = w_word->next;
      w_def = w_def->next;
      cont = cont + 1;

    }
    //assert(z == len);
  }
  return status;
}

/*
returns the amount of nodes to skip when adding a new word
static int nodes_to_skip(dict_t dict, string word) {
  unsigned int numberToSkip = 0;
  return numberToSkip;
}
*/

dict_t dict_empty(void) { 
  dict_t dic = malloc(sizeof(struct _dict_t));
  dic->size = 0u;
  dic->def = NULL;
  dic->word = NULL;
  return dic;
}


static node_t create_node(string elem) {
  node_t node = malloc(sizeof(struct _node_t));
  node->cadena = elem;
  node->next = NULL;
  return node;
}

static node_t destroy_node(node_t node) {
  free(node);
  return node;
}

dict_t dict_add(dict_t dict, string word, string def) {
  invrep(dict);
  
  node_t word_node = create_node(word);
  node_t def_node = create_node(def);
  
  //Caso facil
  if (dict->word == NULL && dict->def == NULL){
    dict->def = def_node;
    dict->word = word_node;
  }

  //Caso con mas de 1 nodo
  else{

    //La palabra no esta
    if (dict_search(dict,word) == NULL){
      node_t w_word,w_def;
      unsigned int size = dict->size;
      unsigned int cont = 1u;
      w_word = dict->word; // apunto al primer nodo de word
      w_def = dict->def; // apunto al primer nodo de def

      while(string_less(w_word->cadena, word) && cont < size){
        w_word = w_word->next;
        w_def = w_def->next;
        cont = cont +1;
      }

      //Meter entre medio
      if (cont < size){
        //guardo el sig
        word_node->next = w_word->next;
        def_node->next = w_def->next;

        //desvio el nodo
        w_word->next = word_node;
        w_def->next = def_node;

        //Intercabio los valores
        string auxW,auxD;

        auxW = w_word->cadena;
        auxD = w_def->cadena;

        w_word->cadena = word_node->cadena;
        w_def->cadena = def_node->cadena;

        word_node->cadena = auxW;
        def_node->cadena = auxD;
      }

      //Ultimo nodo
      else{
        w_word->next = word_node;
        w_def->next = def_node;
      }
      
    }

    //La palabra ya esta
    else{
      node_t w_word,w_def;
      w_word = dict->word; // apunto al primer nodo de word
      w_def = dict->def; // apunto al primer nodo de def

      //Itero hasta encontrar la palabra
      while(!string_eq(w_word->cadena, word)){
        w_word = w_word->next;
        w_def = w_def->next;
      }
      //Edito la palabra
      w_def->cadena = def;
    }
  }
  dict->size = dict->size + 1;
  assert(string_eq(def,dict_search(dict, word)));
  return dict;
}


string dict_search(dict_t dict, string word) {
  string def = NULL;
  if (dict->word != NULL && dict->def != NULL){
    node_t w_word,w_def;
    unsigned int cont = 1u;

    w_word = dict->word; // apunto al primer nodo de word
    w_def = dict->def; // apunto al primer nodo de def

    //Itero hasta encontrar la palabra
    while(!string_eq(w_word->cadena, word) && cont < dict->size){
      w_word = w_word->next;
      w_def = w_def->next;
      cont = cont + 1;
    }
    //Encuentro la def
    if (string_eq(w_word->cadena, word)){
      def = w_def->cadena;
      printf("la palabra %s",string_ref(w_def->cadena));  
    }

  }
  assert((def != NULL) == dict_exists(dict, word));
  return def;
}

bool dict_exists(dict_t dict, string word) {
  bool status = false;

  if (dict->word != NULL && dict->def != NULL){
    node_t w_word;
    unsigned int cont = 1u;

    w_word = dict->word; // apunto al primer nodo de word
    
    //Itero hasta encontrar la palabra
    while(!string_eq(w_word->cadena, word) && cont < dict->size){
      w_word = w_word->next;
      cont = cont + 1;
    }
    //Chequeo si es la palabra que busco
    if (string_eq(w_word->cadena, word)){
      status = true;
    }
  }
  return status;
}

unsigned int dict_length(dict_t dict) {
  return dict->size;
}

// returns the position of the word on the list of nodes (0 being the first node)
// returns -1 if the word is not on the dict
static int find_index_of_key(dict_t dict, string word) {
  int index = 0;

  bool status = false;
  if (dict->word != NULL && dict->def != NULL){
    node_t w_word;
    unsigned int cont = 1u;

    w_word = dict->word; // apunto al primer nodo de word
    
    //Itero hasta encontrar la palabra
    while(!string_eq(w_word->cadena, word) && cont < dict->size){
      w_word = w_word->next;
      cont = cont + 1;
      index = index + 1;
    }
    //Chequeo si es la palabra que busco
    if (string_eq(w_word->cadena, word)){
      status = true;
    }
  }
  index = (status == true) ? index : -1;
  return index;
}


// removes the "index" element of the "list" list of nodes
static node_t remove_on_index(node_t list, int index) {
  node_t nodo,atras; 
  int cont = 0;  
  nodo = list;
  atras = nodo;

  while(cont != index){
    atras = nodo;
    nodo = nodo->next;
  }

  //Nodo entre medio o el ultimo
  if (index != 0){
    atras->next = nodo->next;
    destroy_node(nodo);
  }

  //Unico nodo
  else{
    destroy_node(nodo);
    list = NULL;
  }
  return list;
}

dict_t dict_remove(dict_t dict, string word) {
  assert(invrep(dict));
  int index = find_index_of_key(dict, word);
  if (index != -1) {
    dict->word = remove_on_index(dict->word, index);
    dict->def = remove_on_index(dict->def, index);
    dict->size = dict->size -1;
  }
  assert(invrep(dict));
  return dict;
}

dict_t dict_remove_all(dict_t dict) {
  unsigned int len = dict->size;
  for (int i=0; i < (int)len; i++){
    dict->word = remove_on_index(dict->word, i);
    dict->def = remove_on_index(dict->def, i);
    dict->size = dict->size -1;
  }
  assert(dict->size == 0);
  return dict;
}

/* tip: use fprintf(file, "%s : %s\n", string_ref(word), string_ref(def)); to save to file  */ 
void dict_dump(dict_t dict, FILE *file){
  unsigned int len = dict->size;
  node_t w_word,w_def;
  string word,def;
  w_word = dict->word;
  w_def = dict->def;
  for (int i=0; i < (int)len; i++){
    word = w_word->cadena;
    def = w_def->cadena;
    fprintf(file, "%s : %s\n", string_ref(word), string_ref(def));
    w_word = w_word->next;
    w_def = w_def->next;
  }
  //dict_to_file(dict,file);
}


dict_t dict_destroy(dict_t dict) {
  dict = dict_remove_all(dict);
  free(dict);
  dict = NULL;
  return dict;
}
