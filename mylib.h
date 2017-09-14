/*
 * Common library functions for COSC242 Assigment 1.
 * Includes memory allocation,input handling and printing container key.
 * See mylib.c for function comments.
 */

#ifndef MYLIB_H_
#define MYLIB_H_
#include <stddef.h>

/* Allocates memory with error checking.
   (see mylib.c for more information) */
extern void *emalloc(size_t size);

/* Reallocates memory with error checking.
   (see mylib.c for more information) */
extern void *erealloc(void *p, size_t s);

/* Prints a container key to stdout.
   (see mylib.c for more information) */
extern void print_key(char* str);

/* Gets a string of from a stream.
   (see mylib.c for more information) */
extern int getword(char *s, int limit, FILE *stream);

#endif
