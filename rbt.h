#ifndef RBT_H_
#define RBT_H_

/*Red Black Tree Header code here*/
typedef struct rbtnode *rbt;

extern rbt rbt_new();
extern rbt rbt_free(rbt b);
extern rbt rbt_insert(rbt b, char* str);

#endif
