#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "rbt.h"

typedef enum { RED, BLACK } rbt_colour;

struct rbtnode {
    char* key;
    rbt_colour colour;
    rbt left, right;
};

#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

rbt assign_string(rbt b, char* str) {
    if (b == NULL) {
        b = rbt_new();
    }
    b->key = emalloc((strlen(str) + 1) * sizeof(char));
    strcpy(b->key, str);
    return b;
}

rbt rbt_new() {
    rbt result = emalloc(sizeof *result);
    result->left = NULL;
    result->right = NULL;    
    result->colour = RED;
    return result;
}

void rbt_preorder_print_colours(rbt b) {
    /* this maybe doesn't need to exist in this form? */
    if (b == NULL) return;
    if (IS_RED(b)) printf("Red: %s\n", b->key);
    else printf("Black: %s\n", b->key);
    rbt_preorder_print_colours(b->left);
    rbt_preorder_print_colours(b->right);
}

void rbt_preorder(rbt b, void function(char* str, FILE* stream), FILE* stream) {
    if (b == NULL || strcmp(b->key, "") == 0) return;
    function(b->key, stream);
    rbt_preorder(b->left, function, stream);
    rbt_preorder(b->right, function, stream);
}

void rbt_print(rbt r, FILE* stream) {
    /* preorder print */
    if (r == NULL) return;
    rbt_preorder(r, print_key, stream);
    fprintf(stream, "\n");
}

int rbt_search(rbt b, char* str) {
    int compare;
    if (b == NULL || strcmp(b->key, "") == 0) {
        return 0;
    }
    compare = strcmp(b->key, str);
    if (compare == 0) {
        return 1;
    } else if (compare > 0) {
        return rbt_search(b->left, str);
    } else {
        return rbt_search(b->right, str);
    }
}

rbt rbt_free(rbt b) {
    if (b == NULL) {
        return NULL;
    }
    rbt_free(b->left);
    rbt_free(b->right);
    if (b->key != NULL) {
        free(b->key);
    }
    free(b);
    return NULL;
}

rbt left_rotate(rbt r) {
    rbt temp = r;
    r = r->right;
    temp->right = r->left;
    r->left = temp;
    return r;
}

rbt right_rotate(rbt r) {
    rbt temp = r;
    r = r->left;
    temp->left = r->right;
    r->right = temp;
    return r;
}

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

rbt rbt_do_insertion(rbt b, char* str){
    /* this is here because setting the root colour is
       problematic with recursion */
    b = rbt_insert(b, str);
    b->colour = BLACK;
    return b;
}

rbt rbt_insert(rbt b, char* str) {
    int compare;
    if (b == NULL || b->key == NULL) {
        b = assign_string(b, str);
    } else {
        compare = strcmp(b->key, str);
        if (compare >= 0) {
            b->left = rbt_insert(b->left, str);
        } else {
            b->right = rbt_insert(b->right, str);
        }
    }
    b = rbt_fix(b);
    return b;
}
