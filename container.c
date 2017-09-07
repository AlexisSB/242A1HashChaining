#include <stdlib.h>
#include <stdio.h>

#include "container.h"
#include "flexarray.h"
#include "rbt.h"
#include "mylib.h"


struct containerrec {
  container_t type;
  void *contents;
};

container container_new(container_t container_type) {
    container new_container = emalloc(sizeof(new_container));
    if (container_type == RED_BLACK_TREE) {
        new_container->contents = rbt_new();
    } else {
        new_container->contents = flexarray_new();
    }
    return new_container;
}

void container_free(container c) {
    if (c->type == RED_BLACK_TREE) {
        rbt_free(c->contents);
    } else {
        flexarray_free(c->contents);
    }
    free(c);
}

void container_add(container c, char *word) {
    printf("Adding %s\n", word);
    if (c->type == RED_BLACK_TREE) {
        c->contents = rbt_insert(c->contents, word);
    } else {
        /*flexarray_append(c->contents, word);
         * Commented out b/c flexarray doesn't work with strings yet
         */
    }
}
