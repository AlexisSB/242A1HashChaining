#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "mylib.h"

/* Memory allocation with error checking.
 * Checks for zero length allocation.
 * Checks for successful allocation.
 * @param size - memory size to allocate.
 * @return void pointer to start of allocated memory. 
 */
void *emalloc(size_t size){
    void *result;
    if (size ==0){
        fprintf(stderr, "Zero length allocation\n");
        exit(EXIT_FAILURE);
    }else{
        result = malloc(size);
        if(NULL == result){
            fprintf(stderr, "Memory allocation fault\n");
            exit(EXIT_FAILURE);
        }
        return result;
    }
}

/* Memory reallocation with error checking.
 * Checks for zero length allocation.
 * Checks for successful allocation.
 * @param p - pointer to memory to reallocation.
 * @param s - size of new memory block.
 * @return void pointer to reallocated memory.
 */
void *erealloc(void *p, size_t s){
  void *result;
  if (s ==0){
      fprintf(stderr, "Zero length reallocation");
      exit(EXIT_FAILURE);
  }else{
      result = realloc(p,s);
      if(NULL == result){
          fprintf(stderr, "Memory Allocation Fault\n");
          exit(EXIT_FAILURE);
      }
      return result;
  }
}

/*
 * Prints a container key to stdout.
 * Used in recursive traverse of flexarray and red-black tree.
 * See flexarray.c and rbt.c.
 * @param str - key string of container.
 */ 
void print_key(char* str) {
    printf(" %s", str);
}

/* Gets a string of certain length from a stream.
 * Function taken from COSC242 Lab manual, page 78.
 * Availible at www.cs.otago.ac.nz/cosc242/pdf/lab-book.pdf.
 * @param s - address to copy the string to.
 * @param limit - maximum length of the string.
 * @param stream - input stream to take string from.
 * @return int the number of character added to the string.
 */
 int getword(char *s, int limit, FILE *stream){
  int c;
  char *w = s;
  /*Tests to make sure everything set up properly*/
  assert(limit >0 && s != NULL && stream != NULL);

  /* skip to the start of the word */
  while (!isalnum(c = getc(stream)) && EOF != c);
    
  if (EOF == c) {
    return EOF;
  } else if (--limit > 0) { /* reduce limit by 1 to allow for the \0 */
    *w++ = tolower(c);
  }
  while (--limit > 0) {
    if (isalnum(c = getc(stream))) {
      *w++ = tolower(c);
    } else if ('\'' == c) {
      limit++;
    } else {
      break;
    }
  }
  *w = '\0';
  return w - s;
}





