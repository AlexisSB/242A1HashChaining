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
 * 
 */ 
void print_key(char* str) {
    fprintf(stream, "%s ", str);
}

/*Recursive print method for an array*/
void print_array(int *a, int n){
  if(n>0){
    printf("%d\n",a[0]);
    print_array(a+1,n-1);
  }
}

/* From lab book may want to get clarification*/
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





