/*
 * Common library functions for COSC242 Assigment 1.
 * Includes memory allocation,input handling and printing container key.
 * See mylib.c for function comments.
 */

#ifndef MYLIB_H_
#define MYLIB_H_
#include <stddef.h>

extern void *emalloc(size_t size);
extern void *erealloc(void *p, size_t s);
extern void print_key(char* str);
extern int getword(char *s, int limit, FILE *stream);

#endif
