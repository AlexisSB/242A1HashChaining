#ifndef CONTAINER_H_
#define CONTAINER_H_

#include <stddef.h>

typedef enum container_e {FLEX_ARRAY, RED_BLACK_TREE} container_t;
typedef struct containerrec *container;

extern container container_new();
extern void container_free(container c);
extern void container_add(container c, char* str);
extern int container_search(container c, char* str);
extern void container_print(container c, FILE *stream);

#endif
