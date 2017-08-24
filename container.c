#include <stdlib.h>
#include <stdio.h>

#include "container.h"

struct containerrec {
  container_t type;
  void *contents;
};

void container_add(container c, char *word) {
  c->type = RED_BLACK_TREE;
  word ="test word";
  printf("%s\n",word);

}
