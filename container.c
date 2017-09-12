#include <stdlib.h>
#include <stdio.h>

#include "container.h"
#include "flexarray.h"
#include "rbt.h"
#include "mylib.h"

/* container struct
 * type: enum (RED_BLACK_TREE or FLEX_ARRAY)
 * contents: pointer to the contents of the rbt or flexarray
 */
struct containerrec {
  container_t type;
  void *contents;
};

/* creates a new container
 * @param container_type: specifies which type (rbt or flexarray) to be created
 * @return newly created container of correct type
 */
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

/* frees all memory associated with a container
   @param c: the container to be freed */
void container_free(container c) {
    if(c !=NULL){
        if (c->type == RED_BLACK_TREE) {
            rbt_free(c->contents);
        } else {
            flexarray_free(c->contents);
        }
    }
    free(c);
}

/* adds a string to a container (rbt/flexarray)
   @param c: the container to which the string is to be added
   @param word: the string to be added */
void container_add(container c, char *word) {
    if (c->type == RED_BLACK_TREE) {
        c->contents = rbt_do_insertion(c->contents, word);
    } else {
        flexarray_append(c->contents, word);
    }
}

/* searches the container (rbt/flexarray)
   @param c: the container to be searched
   @param str: the string to be searched for */
int container_search(container c, char* str) {
    if (c->type == RED_BLACK_TREE) {
        return rbt_search(c->contents, str);
    } else {
        return is_present(c->contents, str);
    }
}

/* prints all items in the container (rbt/flexarray)
   @param c: the container which is to be printed */
void container_print(container c) {
    if (c->type == RED_BLACK_TREE) {
        rbt_print(c->contents);
    } else {
        visit(c->contents, print_key);
    }
}
