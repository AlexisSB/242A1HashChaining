#ifndef CONTAINER_H_
#define CONTAINER_H_

#include <stddef.h>

typedef enum container_e {FLEX_ARRAY, RED_BLACK_TREE} container_t;
typedef struct containerrec *container;

extern void container_new(container c);

#endif
