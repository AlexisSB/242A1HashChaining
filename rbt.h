#ifndef RBT_H_
#define RBT_H_

/* Header file for rbt.c*/

typedef struct rbtnode *rbt;

/* Creates a new rbt.
   (see rbt.c for more information)*/
extern rbt rbt_new();

/* Frees all memory associated with an rbt.
   (see rbt.c for more information)*/
extern rbt rbt_free(rbt r);

/* Inserts a string into an rbt.
   (see rbt.c for more information)*/
extern rbt rbt_do_insertion(rbt r, char* str);

/* Searches an rbt for a specified string.
   (see rbt.c for more information)*/
extern int rbt_search(rbt r, char* str);

/* Preorder prints the key of each node in an rbt.
   (see rbt.c for more information)*/
extern void rbt_print(rbt r);

#endif
