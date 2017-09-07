#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "htable.h"
#include "container.h"

#define DEFAULT_TYPE FLEX_ARRAY


struct htablerec {
    int capacity;
    int num_keys;
    int *frequencies;
    container_t *keys;
};

static unsigned int htable_word_to_int(char *word){
  unsigned int result = 0;
  while (*word != '\0') {
    result = (*word++ + 31 * result);
  }
  return result;
}

void htable_free(htable h){
    int i;
    for (i = 0; i < h->capacity; i++) {
	free(h->keys[i]);
    }
    free(h->keys);
    free(h->frequencies);
    free(h);
}


/* Inserts a string into a hash table.
 * Increments down each time there is a collision.
 * @param h - the hash table. 
 * @param str - string to insert into hash table.
 * @return int the number of times the string has been enterd into the table.
 */
int htable_insert(htable h, char *str){
    unsigned int wordnumber;
    unsigned int hashvalue;
    int counter;
    int HASH_TABLE_FULL = 0;
    /*char *temp;*/

    wordnumber = htable_word_to_int(str);
    hashvalue = wordnumber % (h->capacity);
    counter = 0;
    /*
    if(h->keys[hashvalue] != NULL){
        if(h->keys[hashvalue] =
           container_add
    }
    */
    /*Increments through hash table until finds empty space, finds equal value in table or
     * goes through whole table*/
    while (h->keys[hashvalue] != NULL
	   && strcmp(str, h->keys[hashvalue]) != 0
	   && counter <= h->capacity) {
	hashvalue = (hashvalue + 1) % h->capacity;
	counter++;
    }

    if (h->keys[hashvalue] == NULL) {	/*If new space found */
      h->keys[hashvalue] = emalloc((strlen(str) + 1) * (sizeof str[0]));
	strcpy(h->keys[hashvalue], str);
	h->frequencies[hashvalue] = 1;
	h->num_keys++;
	return h->frequencies[hashvalue];

    } else if (strcmp(str, h->keys[hashvalue]) == 0) {	/* If string is already in table */
	h->frequencies[hashvalue]++;
	return h->frequencies[hashvalue];

    } else {/* if (counter >=h->capacity){ */
	printf("Hash Table Full\n");
	return HASH_TABLE_FULL;
    }
}



htable htable_new(int capacity, container c){
    htable result = emalloc(sizeof *result);
    int i;
    result->capacity = capacity;
    result->num_keys = 0;
    result->frequencies = emalloc(result->capacity * sizeof result->frequencies[0]);
    result->keys = emalloc(result->capacity * sizeof result->keys[0]);
    for (i = 0; i < result->capacity; i++) {
        result->frequencies[i] = 0;
        result->keys[i] = NULL;
    }
    return result;
}

void htable_print(htable h, FILE * stream){
  int i;
  fprintf(stream, "Frequency\tKey\n");
  for(i=0;i<h->capacity;i++){
    if (h->keys[i]!=NULL){
      fprintf(stream, "%d\t\t%s\n",h->frequencies[i],h->keys[i]);
    }
  }
  printf("Exiting print\n");
}

int htable_search(htable h, char *str){
   int num_collisions = 0;
    unsigned int hash_position;
    /*printf("Before hash");*/
    hash_position = htable_word_to_int(str) % h->capacity;
    /* printf("Hash number : %d", hash_position);*/

    while (h->keys[hash_position] != NULL && strcmp(h->keys[hash_position], str) != 0){
        hash_position++;
        hash_position = hash_position%h->capacity;
        num_collisions++;
        if(num_collisions == h->capacity){
            printf("Table full, value not found\n");
            return 0;
        }
    }
    if (h->keys[hash_position] == NULL){
        return 0;
    }else{
        return h->frequencies[hash_position];
    }    
        
}
