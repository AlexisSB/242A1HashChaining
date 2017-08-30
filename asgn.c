#include <stdio.h>
#include <stdlib.h>

#define MALLOC_DEBUG
#include "mylib.h"
#include "container.h"
#include "flexarray.h"
#include "htable.h"
/*#define MALLOC_DEBUG*/

#include "rbt.h"
/*#define MALLOC_DEBUG*/


int main(void){
  htable h;
  char *p = emalloc((sizeof (char)) *10);
  printf("Hello World!\n");
  p[1] = 'H';
  h = htable_new(100);
  htable_insert(h,"hello");
  htable_insert(h,"world");
  htable_print(h,stdout);
  htable_free(h);
  free(p);
  return EXIT_SUCCESS;
  
}
        
