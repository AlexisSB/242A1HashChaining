#ifndef HTABLE_H_
#define HTABLE_H_
#include <stdio.h>
#include "container.h"

/* header file for htable.c */

typedef struct htablerec *htable;

/* frees all memory associated with htable
   (see htable.c for more information) */
extern void   htable_free(htable h);

/* inserts string into htable
   (see htable.c for more information) */
extern void   htable_insert(htable h, char *str);

/* creates new htable
   (see htable.c for more information) */
extern htable htable_new(int capacity, container_t type);

/* prints all items in htable
   (see htable.c for more information) */
extern void   htable_print(htable h, FILE *stream);

/* searches for string in htable
   (see htable.c for more information) */
extern int    htable_search(htable h, char *str);

#endif
