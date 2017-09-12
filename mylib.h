#ifndef MYLIB_H_
#define MYLIB_H_
#include <stddef.h>

extern void *emalloc(size_t size);
extern void *erealloc(void *p, size_t s);

extern void print_key(char* str);

extern void merge_sort(int *array,int len,int *workspace);
extern void quick_sort(int *array, int size);
extern void insertion_sort(int *array, int size);
extern void print_array(int *a,int size);
extern int getword(char *s, int limit, FILE *stream);

#endif
