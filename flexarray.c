#include <stdio.h>
#include <stdlib.h>

#include "flexarray.h"
#include "mylib.h"

/* Flex array code here*/
struct flexarrayrec {
    int capacity;
    int itemcount;
    int *items;
};

flexarray flexarray_new() {
    flexarray result = emalloc(sizeof *result);
    result->capacity = 2;
    result->itemcount = 0;
    result->items = emalloc(result->capacity * sizeof result->items[0]);
    return result;
}

void flexarray_append(flexarray f, int num) {
    if (f->itemcount == f->capacity) {
        f->capacity = f->capacity*2;
        f->items = erealloc(f->items,f->capacity*sizeof f->items[0]);
    }
    f->items[f->itemcount] = num;
    f->itemcount++;
}

void flexarray_print(flexarray f) {
    int i;
    for(i=0;i<f->itemcount;i++){
        printf("%d\n",f->items[i]);
    }
}
/* Are we doing any sorting for assignment?*/
void flexarray_sort(flexarray f) {
    /*For quick sort*/
    quick_sort(f->items,f->itemcount);
}

void flexarray_mergesort(flexarray f){
    /*printf("sorting, need %i items, or %i bytes\n", f->itemcount, f->itemcount);*/
    int *workspace = emalloc(f->itemcount*sizeof(f->items[0]));
    /*printf("allocated\n");*/
    merge_sort(f->items,f->itemcount,workspace);
    /*printf("sorted\n");*/
    free(workspace);
}

void flexarray_free(flexarray f) {
    free(f->items);
    free(f);
}

int flexarray_size(flexarray f){
    return f->itemcount;
}
