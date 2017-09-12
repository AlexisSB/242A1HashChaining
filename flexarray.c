#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "flexarray.h"
#include "mylib.h"

/* flexarray struct
   capacity:  maximum capacity of the flexarray
   itemcount: number of items currently in the flexarray
   items: the array itself, an array of strings */
struct flexarrayrec {
    int capacity;
    int itemcount;
    char **items;
};

/* creates a new (empty) flexarray
   allocates enough memory for a new flexarray and the array of strings
   @return the newly created empty flexarray */
flexarray flexarray_new() {
    flexarray result = emalloc(sizeof *result);
    result->capacity = 2;
    result->itemcount = 0;
    result->items = emalloc(result->capacity * sizeof result->items[0]);
    return result;
}

/* appends an item to the flexarray
   @param f: the flexarray to which the item will be appended
   @param *str: the string to be appended */
void flexarray_append(flexarray f, char *str) {
    if (f->itemcount == f->capacity) {
        f->capacity = f->capacity*2;
        f->items = erealloc(f->items,f->capacity*sizeof f->items[0]);
    }
    f->items[f->itemcount] = emalloc((strlen(str)+1) * sizeof f->items[f->itemcount][0]);
    strcpy(f->items[f->itemcount], str);
    f->itemcount++;
}

/* frees the memory associated with the flexarray
   @param f: the flexarray to be freed */
void flexarray_free(flexarray f) {
    int i;
    for (i=0; i<f->itemcount; i++) {
        free(f->items[i]);
    }
    free(f->items);
    free(f);
}

/* @return the current size of the flexarray
   @param f: the flexarray we want the size of */
int flexarray_size(flexarray f){
    return f->itemcount;
}

/* searches the flexarray for a string
   @param f: the flexarray to be searched
   @param str: the string to be searched for
   @return 1 if the string is in the flexarray, 0 if not */
int is_present(flexarray f, char* str) {
    int i;
    for (i=0; i < f->itemcount; i++) {
        if (strcmp(f->items[i], str) == 0) {
            return 1;
        } 
    }
    return 0;
}

/* runs a function on every item in the flexarray
   @param a: the flexarray to be traversed
   @param f: the function to be run (takes a string and a file as params)*/
void visit(flexarray a, void f(char* str, FILE* stream)) {
    int i;
    for (i=0; i < a->itemcount; i++) {
        f(a->items[i], stdout);
    }
    fprintf(stdout, "\n");
}

