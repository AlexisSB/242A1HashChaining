#include <stdlib.h>
#include <stdio.h>

#include "container.h"

struct containerrec {
  container_t type;
  void *contents;
};

/*Returns 1/0 to indicate added successfully or error*/
int container_add(container c, char *word) {
    printf("%s\n",word);
    if (c->type == RED_BLACK_TREE) {
        c-> contents = rbt_insert(c->contents,word);
    }else{
        flexarray_append(c->contents,word);
    }
    
    return 1;
 
}

void container_free(container c){
   if (c->type == RED_BLACK_TREE) {
     rbt_free(c);
    }else{
     flexarray_free(c);
    }
}
