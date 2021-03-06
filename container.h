#ifndef CONTAINER_H_
#define CONTAINER_H_

#include <stddef.h>

/* Header file for container.c*/

typedef enum container_e {FLEX_ARRAY, RED_BLACK_TREE} container_t;
typedef struct containerrec *container;

/* Creates new (empty) container.
   (see container.c for more information)*/
extern container container_new(container_t container_type);

/* Frees all memory associated with container.
   (see container.c for more information)*/
extern void container_free(container c);

/* Adds string to container (rbt/flexarray).
   (see container.c for more information)*/
extern void container_add(container c, char* word);

/* Searches for string in container.
   (see container.c for more information)*/
extern int container_search(container c, char* str);

/* Prints every string in the container.
   (see container.c for more information)*/
extern void container_print(container c);


#endif
