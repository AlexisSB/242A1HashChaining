#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "flexarray.h"
#include "mylib.h"

/* Flex array code here*/
struct flexarrayrec {
    int capacity;
    int itemcount;
    char **items;
};

flexarray flexarray_new() {
    flexarray result = emalloc(sizeof *result);
    result->capacity = 2;
    result->itemcount = 0;
    result->items = emalloc(result->capacity * sizeof result->items[0]);
    return result;
}

void flexarray_append(flexarray f, char *str) {
    if (f->itemcount == f->capacity) {
        f->capacity = f->capacity*2;
        f->items = erealloc(f->items,f->capacity*sizeof f->items[0]);
    }
    f->items[f->itemcount] = str;
    f->itemcount++;
}


void flexarray_free(flexarray f) {
    free(f->items);
    free(f);
}

int flexarray_size(flexarray f){
    return f->itemcount;
}

int is_present(flexarray f, char* str) {
    /* this should maybe not use a sequential search */
    int i;
    for (i=0; i < f->itemcount; i++) {
        if (strcmp(f->items[i], str) == 0) {
            return 1;
        } 
    }
    return 0;
}

void visit(flexarray a, void f(char* str)) {
    int i;
    for (i=0; i < a->itemcount; i++) {
        f(a->items[i]);
    }
}

void flexarray_print(char *str){
    printf("%s\n", str);
}
