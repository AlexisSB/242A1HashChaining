#ifndef RBT_H_
#define RBT_H_

/*Red Black Tree Header code here*/
typedef struct rbtnode *rbt;

extern rbt rbt_new();
extern rbt rbt_free(rbt r);
extern rbt rbt_do_insertion(rbt r, char* str);
extern rbt rbt_insert(rbt r, char* str);
extern int rbt_search(rbt r, char* str);
extern void rbt_print(rbt r, FILE* stream);

#endif
