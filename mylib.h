#ifndef MYLIB_H_
#define MYLIB_H_
#include <stddef.h>

/*Comment out to remove malloc debugging info*/
/*#define MALLOC_DEBUG*/

#ifdef MALLOC_DEBUG
#define emalloc(size) do_debug_emalloc(__LINE__,__FILE__,size)
extern void *do_debug_emalloc(long line,char *file,size_t size);
#else
#define emalloc(size) do_normal_emalloc(size)
extern void *do_normal_emalloc(size_t size);
#endif

extern void *erealloc(void *p, size_t s);

extern void print_key(char* str);

extern void merge_sort(int *array,int len,int *workspace);
extern void quick_sort(int *array, int size);
extern void insertion_sort(int *array, int size);
extern void print_array(int *a,int size);
extern int getword(char *s, int limit, FILE *stream);

#endif
