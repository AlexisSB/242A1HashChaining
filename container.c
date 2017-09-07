#include <stdlib.h>
#include <stdio.h>

#include "container.h"

struct containerrec {
  container_t type;
  void *contents;
};

void container_add(container c, char *word) {
    printf("%s\n",word);
    if (c->type = RED_BLACK_TREE) {
        c-> contents = rbt_insert(c->contents,word);
    }else{
        flexarray_append(c->contents,word);
    }
 
}
