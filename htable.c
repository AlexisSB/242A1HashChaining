#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "htable.h"
#include "container.h"
#include "rbt.h"
#include "flexarray.h"


struct htablerec {
    int capacity;
    int num_keys;
    container_t container_type;
    container *keys;
};

htable htable_new(int capacity, container_t c){
    htable result = emalloc(sizeof *result);
    int i;
    result->capacity = capacity;
    result-> num_keys = 0;
    result->container_type = c;
    if (c == FLEX_ARRAY){
        printf("Making flex array\n");
	result->keys = emalloc((result->capacity) * sizeof(flexarray));
    }else{
        printf("Making rbt \n");
	result->keys = emalloc(result->capacity * sizeof(rbt));
        /*printf("done new rbt emalloc\n");*/
    }

    for (i=0;i<capacity;i++){
	result->keys[i] = NULL;
    }
    
    return result;
}


void htable_free(htable h){
    int i;
    for (i=0;i<h->capacity;i++){
	container_free(h->keys[i]);
    }
    /*printf("Freed containers\n");*/
    free(h->keys);
    /* printf("Freed array\n");*/
    free(h);
}

static unsigned int htable_word_to_int(char *word){
  unsigned int result = 0;
  while (*word != '\0') {
    result = (*word++ + 31 * result);
  }
  return result;
}

int htable_insert(htable h, char *str){
    unsigned int wordnumber;
    unsigned int hashvalue;
    int result;
    
    wordnumber = htable_word_to_int(str);
    hashvalue = wordnumber % (h->capacity);
    if (h->keys[hashvalue] == NULL){
        h->keys[hashvalue] = container_new(h->container_type);
    }
    result = container_add(h->keys[hashvalue],str);
    
    return result;
}

void htable_print(htable h , FILE *stream){
    int i;
    /*fprintf(stream, "Key\n");*/
    for (i =0; i<h->capacity;i++){
        if (h->keys[i] != NULL){
          fprintf(stream,"%-6d",i);
          container_print(h->keys[i],stream);
      }
    }
}

int htable_search(htable h, char *str){
  unsigned int wordnumber;
  unsigned int hashvalue;
  int result;
  int KEY_NOT_FOUND = 0;

  wordnumber = htable_word_to_int(str);
  hashvalue = wordnumber % (h->capacity);
  if (h->keys[hashvalue] ==NULL){
      return KEY_NOT_FOUND;
  }else{

  result = container_search(h->keys[hashvalue],str);

  return result;
  }

}

    
