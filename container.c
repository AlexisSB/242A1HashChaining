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
    container new_container = emalloc(sizeof(*new_container));
    new_container->type =container_type;
    
    if (container_type == RED_BLACK_TREE) {
        new_container->contents = rbt_new();
    } else {
        new_container->contents = flexarray_new();
    }
    return new_container;
}

void container_free(container c) {
    printf("hello i'm container free\n");
    if(c !=NULL){
        if (c->type == RED_BLACK_TREE) {
            printf("Starting rbt free\n");
            rbt_free(c->contents);
        } else {
            printf ("Flexifree\n");
            flexarray_free(c->contents);
        }
    }
    printf("final free\n");
    free(c);
}

void container_add(container c, char *word) {
    if (c->type == RED_BLACK_TREE) {
        c->contents = rbt_do_insertion(c->contents, word);
    } else {
        flexarray_append(c->contents, word);
    }
}

int container_search(container c, char* str) {
    if (c->type == RED_BLACK_TREE) {
        return rbt_search(c->contents, str);
    } else {
        return is_present(c->contents, str);
    }
}

void container_print(container c, FILE* stream) {
    if (c->type == RED_BLACK_TREE) {
        rbt_print(c->contents, stream);
    } else {
        visit(c->contents, print_key);
    }
}
