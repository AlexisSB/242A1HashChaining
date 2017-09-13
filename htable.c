#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "htable.h"
#include "container.h"
#include "rbt.h"
#include "flexarray.h"

/* Hash table struct.
 * capacity - total capacity of the hash table
 * num_keys - number of items currently held in the hash table
 * container_type - type of container used in htable (RED_BLACK_TREE/FLEX_ARRAY)
 * keys - pointer to rows in the hash table.
 */
struct htablerec {
    int capacity;
    int num_keys;
    container_t container_type;
    container *keys;
};

/* Creates a new hash table.
 * Allocates memory required for a new htable.
 * @param capacity - how big the htable will be
 * @param c - which type of container the htable should use
 * @return newly created htable
 */
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

/* Frees the memory associated with the hash table.
 * @param h - the htable to be freed
 */
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

/* Converts string to an int for generating hash value.
 * @param word - the string to be turned into an int
 * @return the resulting int value.
 */
static unsigned int htable_word_to_int(char *word){
  unsigned int result = 0;
  while (*word != '\0') {
    result = (*word++ + 31 * result);
  }
  return result;
}

/* Inserts an item into the hash table.
 * @param h - the htable to which the item will be inserted
 * @param *str - the string to be inserted 
 */
void htable_insert(htable h, char *str){
    unsigned int wordnumber;
    unsigned int hashvalue;
      
    wordnumber = htable_word_to_int(str);
    hashvalue = wordnumber % (h->capacity);
    if (h->keys[hashvalue] == NULL){
        h->keys[hashvalue] = container_new(h->container_type);
    }
    container_add(h->keys[hashvalue],str);
}

/* Prints every item in the hash table.
 * @param h - the htable to be printed
 * @param stream - output stream for printing.
 */
void htable_print(htable h , FILE *stream){
    int i;
    /*fprintf(stream, "Key\n");*/
    for (i =0; i<h->capacity;i++){
        if (h->keys[i] != NULL){
          fprintf(stream,"%-6d",i);
          container_print(h->keys[i]);
      }
    }
}

/* Searches the hashtable for a given string.
 * @param h: the htable to be searched
 * @param str: the string to be searched for
 * @return 0 if the string is NOT in the htable, else returns 1
 */
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

    
