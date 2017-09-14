#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "rbt.h"

/* Macros for determining the colour of an rbt node. */
#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

/* Enum for the possible colour values of each rbt node. */
typedef enum { RED, BLACK } rbt_colour;

/* Red Black Tree node struct.
 * key - root node key
 * colour - colour of root node (red/black)
 * left - left subtree.
 * right - rigth subtree.
 */
struct rbtnode {
    char* key;
    rbt_colour colour;
    rbt left, right;
};

/* Allocates memory for a new red-black tree.
 * Sets key, left, and right to null. 
 * @return new empty red-black tree
 */
rbt rbt_new() {
    rbt result = emalloc(sizeof *result);
    result->key =NULL;
    result->left = NULL;
    result->right = NULL;    
    result->colour = RED;
    return result;
}

/* Preorder traverses a specified red-black tree.
 * Calls a specified function on the key of each node.
 * @param r Red-black tree to traverse
 * @param function Function to be called on each node's key
 */
void rbt_preorder(rbt r, void function(char* str)) {
    if (r == NULL || strcmp(r->key, "") == 0) return;
    function(r->key);
    rbt_preorder(r->left, function);
    rbt_preorder(r->right, function);
}

/* Prints each node of a specified red-black tree to stdout.
 * Nodes are printed in preorder.
 * @param r Red-black tree to be printed
 */
void rbt_print(rbt r) {
    if (r == NULL) return;
    rbt_preorder(r, print_key);
    fprintf(stdout, "\n");
}

/* Search a specified red-black tree for a specified value.
   @param r Red-black tree to be searched
   @param str String to search for
   @return int Returns 1 if the value is found, 0 if not
 */
int rbt_search(rbt r, char* str) {
    int compare = 0;
    if (r == NULL || strcmp(r->key, "") == 0) {
        return 0;
    }
    compare = strcmp(r->key, str);
    if (compare == 0) {
        return 1;
    } else if (compare > 0) {
        return rbt_search(r->left, str);
    } else {
        return rbt_search(r->right, str);
    }
}

/* Frees all memory associated with a specified red-black tree.
 * @param r Red-black tree to free
 * @return Always returns NULL
 */
rbt rbt_free(rbt r) {
    if (r != NULL) {
        rbt_free(r->left);
        rbt_free(r->right);
        if (r->key != NULL) {
            free(r->key);
        }
        free(r);
    }
    return NULL;
}

/* Rotates a specified red-black tree left.
 * @param r Red-black tree to rotate
 */
rbt left_rotate(rbt r) {
    rbt temp = r;
    r = r->right;
    temp->right = r->left;
    r->left = temp;
    return r;
}

/* Rotates a specified red-black tree right.
   @param r Red-black tree to rotate
 */
rbt right_rotate(rbt r) {
    rbt temp = r;
    r = r->left;
    temp->left = r->right;
    r->right = temp;
    return r;
}

/* Performs rotations and recolourings required to
 * maintain the black-height properties of a
 * specified red-black tree.
 * @param r Red-black tree to fix
 */
rbt rbt_fix(rbt r) {
    if (r->left != NULL && IS_RED(r->left)) {/*Has a red left child*/
        if (IS_RED(r->left->left)) {/*left left is red*/
            if (IS_RED(r->right)) {/*right is black*/
                /*make R red, make R's children black*/
                r->colour = RED;
                r->left->colour = BLACK;
                r->right->colour = BLACK;
            } else {
                /*right rotate R, make new root black, make R red*/
                r = right_rotate(r);
                r->colour = BLACK;
                r->right->colour = RED;
            }
        } else if (IS_RED(r->left->right)) {/*red left, left right red*/
            if (IS_RED(r->right)) {
                /*make R red, make R's children black*/
                r->colour = RED;
                r->left->colour = BLACK;
                r->right->colour = BLACK;
            } else {
                /*left rotate left child of R, right rotate R
                //make new root black, make R red*/
                r->left = left_rotate(r->left);
                r = right_rotate(r);
                r->colour = BLACK;
                r->right->colour = RED;
            }
        }
    }
    if (r->right != NULL && IS_RED(r->right)) {/*right red and not null*/
        if (IS_RED(r->right->left)) {/*right left red*/
            if (IS_RED(r->left)) {
                /*make R red, make R's children black*/
                r->colour = RED;
                r->left->colour = BLACK;
                r->right->colour = BLACK;
            } else {
                /*right rotate right child of R, left rotate R
                //make new root black, make R red*/
                r->right = right_rotate(r->right);
                r = left_rotate(r);
                r->colour = BLACK;
                r->left->colour = RED;
            }
        } else if (IS_RED(r->right->right)) {
            if (IS_RED(r->left)) {
                /*make R red, make R's children black*/
                r->colour = RED;
                r->left->colour = BLACK;
                r->right->colour = BLACK;
            } else {
                /*left rotate R, make new root black, make R red*/
                r = left_rotate(r);
                r->colour = BLACK;
                r->left->colour = RED;
            }
        }
    }
    return r;
}

/* Inserts a specified string to into a specified red-black tree.
 * To maintain all red-black properties, this function should
 * only be called through rbt_do_insertion.
 * @param r Red-black tree to insert into
 * @param str String value to insert
 * @return rbt The new state of the red-black tree
 */
rbt rbt_insert(rbt r, char* str) {
    int compare = 0;
    if (r == NULL){
        r = rbt_new();
    }
    if (r->key == NULL) {
        r->key = emalloc((strlen(str) + 1) * sizeof(char));
        strcpy(r->key, str);
        r->colour = RED;
    } else {
        compare = strcmp(r->key, str);
        if (compare >= 0) {
            r->left = rbt_insert(r->left, str);
        } else {
            r->right = rbt_insert(r->right, str);
        }
    }
    
    r = rbt_fix(r);
    return r;
}

/* Inserts a specified string value into a specified red-black tree.
 * Red-black properties are maintained.
 * @param r Red-black tree to insert into
 * @param str String value to insert
 * @return rbt The new state of the red-black tree
 */
rbt rbt_do_insertion(rbt r, char* str){
    r = rbt_insert(r, str);
    r->colour = BLACK;
    return r;
}
