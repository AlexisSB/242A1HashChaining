#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "htable.h"
#include "container.h"
#include "rbt.h"
#include "flexarray.h"

#define DEFAULT_TYPE FLEX_ARRAY


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
	result->keys = emalloc((result->capacity) * sizeof(flexarray));
    }else{
	result->keys = emalloc(result->capacity * sizeof(rbt));
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
    free(h->keys);
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
    int counter;
    int result;

    wordnumber = htable_word_to_int(str);
    hashvalue = wordnumber % (h->capacity);
    counter = 0;

    result = container_add(h->keys[hashvalue],str);
    
    return result;
}

void htable_print(htable h , FILE *stream){
    int i;
    fprintf(stream, "Key\n");
    for (i =0; i<h->capacity;i++){
	container_print(h->keys[i],stream);
    }
    


}

int htable_search(){
}
    
