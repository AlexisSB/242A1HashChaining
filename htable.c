#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "htable.h"

struct htablerec{
  int num_items;
};

void htable_free(htable h){
  free(h);
}

int htable_insert(htable h, char *str){
  h->num_items = 1;
  str = "test insert";
  printf("%s\n", str);
  return 0;
}

htable htable_new(int capacity){
  htable h;
  h = malloc(sizeof h);
  h->num_items =capacity;
  
  return h;
}

void htable_print(htable h, FILE *stream){
  
  fprintf(stream, "%d\n", h->num_items);
}

int htable_search(htable h, char *str){
  h->num_items = 1;
  str = "test search";
  printf("%s\n", str);
  return 0;
}
