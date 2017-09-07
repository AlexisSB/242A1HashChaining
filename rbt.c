#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rbt.h"
#include "mylib.h"

#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

typedef enum {RED, BLACK} rbt_colour;

struct rbt_node { 
  char *key;
  rbt left;
  rbt right;
  rbt_colour colour;
  
};

int rbt_search(rbt b, char *key) {
  int comparision;
  int KEY_FOUND =1;
  int KEY_NOT_IN_TREE =0;

  if (b == NULL || NULL==b->key){
    /*printf("Null Tree\n");*/
    return KEY_NOT_IN_TREE;
  }
  
  comparision = strcmp(key, b->key);
  
  if (comparision ==0){
    /*    printf("Key found at root\n");*/
    return KEY_FOUND;
    
  }else if (comparision > 0){/*target  greater than b->key*/
    return  rbt_search(b->right, key);
   
  }else{/*target less than key*/
    return rbt_search(b->left,key);
  }

}

rbt rbt_fix(rbt b){
  /*if root is black
   * - check down to grandchildren for pairs:
   * - look left and fix.
   * - look right and fix
   * If root is red
   * - can only be red if newly inserted.
   * - shouldnt' need to do anything?
   * - check colour of children and fix if any red.
   * Will have to check all the things are not null.
   */
  rbt left_child = b->left;
  rbt right_child = b->right;

  /*Null empty tree condition*/
  if (left_child == NULL || right_child ==NULL){
    return b;
  }
  
  if (IS_BLACK(b)){

    /*If children black then apply rbt fix to each grandchild*/
    if (IS_BLACK(left_child) || IS_BLACK(right_child)){
      b = rbt_fix(b->left->left);
      b = rbt_fix(b->left->right);
      /*Fix here*/
      b = rbt_fix(b->right->left);
      b = rbt_fix(b->right->right);
      return b;
      
    }else{

     
      if (IS_RED(left_child) && IS_RED(left_child->left)){
	/* red left child, red left left child */

	if (IS_RED(right_child)){/* right child red option to fix tree*/
	  b->colour = RED;
	  b->left = BLACK;
	  b->right = BLACK;
	  return b;
	  
	}else{
	 
	  b->colour = RED;
	  b->left->colour = BLACK;
	  b = right_rotate(b);
	  return b;
	}
	  
      }else if (IS_RED(left_child) && IS_RED(left_child->right)){
	/* red left child, red left right child*/
	if (IS_RED(right_child)){/* right child red option to fix tree*/
	  b->colour = RED;
	  b->left = BLACK;
	  b->right = BLACK;
	  return b;
	  
	}else{
	  b->left->right = BLACK;
	  b->colour = RED;
	  b->left = left_rotate(b->left);
	  b = right_rotate(b);
	  return b;
	}
		
      }else if (IS_RED(right_child) && IS_RED(right_child->left)){
	/*red right child, red left right child*/

	
      }else if (IS_RED(right_child) && IS_RED(right_child->right)){
	/* red right child, red right right child*/
	
      }
      
      
      
      if(IS_RED(left_child)){/*Red left child, check left grandchildren*/
	
	if(IS_RED(left_child->left)){
	  /*Red left child, red left grandchild*/

	  if(IS_RED(right_child)){/*Check right child to determine what to do*/
	    /*Action - recolour*/
	    b->colour = RED;
	    left_child->colour = BLACK;
	    right_child->colour = BLACK;
	    return b;
	    
	  }else{
	    /*Action right rotate root and recolour*/
	    b->colour =RED;
	    left_child->colour = BLACK;
	    b = right_rotate(b);
	    return b;
	  }
	}else{
	  /* If left child red, left left grandchild black
	   * shouldn't be any rbt conflict*/
	}else if(left_child->right->colour ==RED){
	  /* Left
	  /*Do table thing recolour and rotate.*/
	}
	
      }
      if(right_child->colour == RED){
      }
    } 
  }else{
  }

}

/* must use assign when using rbt_insert
 * e.g. b = rbt_insert(b,newstr)
 */
rbt rbt_insert(rbt b, char *str){
  int comparision;
  
  /*empty tree*/
  /*printf("Starting insert\n");*/
  if (b->key ==NULL){
    /*printf("starting alloc\n");*/
    b->key = emalloc((strlen(str)+1)*sizeof str[0]);
    strcpy(b->key,str);
    /*IS this the only place colour set and fix needed?*/
    b->colour = RED;
    rbt_fix(b);
    return b;
  }
  /*key equal to root*/
  comparision = strcmp(str, b->key);

  if (comparision ==0){
    printf("Key equal to root");
    return b;
  }else if(comparision >0){ /*key greater than root*/
    /* Not sure if this neccessary??*/
    if (b->right ==NULL){
      b->right = rbt_new();
    }
    b->right = rbt_insert(b->right,str);
    rbt_fix(b);
    return b;
  }else{  /*key less than root*/
    if(b->left ==NULL){
      b->left = rbt_new();
    }
    b->left = rbt_insert(b->left,str);
    rbt_fix(b);
    return b;
  }
}

void print_key(char *s) {
  printf("%s\n", s);
}

void rbt_inorder(rbt b, void f(char *str)){
  /*printf("In inorder\n");*/
  if(b==NULL ||b->key ==NULL){
    /*printf("Empty Tree");*/
    return;
  }
  /*printf("Past empty tree\n");*/
  rbt_inorder(b->left,f);
  /*printf("At root\n");*/
  f(b->key);
  /*
  if(IS_BLACK(b)){
      printf("BLACK\n");
    }else{
      printf("RED\n");
    }
  */
  rbt_inorder(b->right, f);
}  

void rbt_preorder(rbt b, void f(char *str)){
  if(b==NULL ||b->key ==NULL){
    return;
  }
  f(b->key);
  rbt_preorder(b->left,f);
  rbt_preorder(b->right,f);
}

void rbt_postorder(rbt b, void f(char *str)){
  if(b==NULL ||b->key ==NULL){
    return;
  }
  
  rbt_postorder(b->left,f);
  rbt_postorder(b->right,f);
  f(b->key);
}

rbt rbt_new(){
  /*allocate memory*/
  /*create new*/
  rbt b = emalloc(sizeof *b);
  
  b->key = NULL;
  b->left = NULL;
  b->right = NULL;
   
  return b;
}

rbt rbt_delete(rbt b, char *str){
  int comparision;
  rbt temp;
  char *temp_string;
  if (b ==NULL || b->key == NULL){
    /*printf("Tree empty");*/
    return b;
  }

  comparision = strcmp(str,b->key);
    /*printf("%d\n", comparision);*/

  if (comparision ==0){/*Desired key a current node*/
    /*delete node*/
    if(b->left ==NULL && b->right == NULL){/*node is a leaf*/
      free(b->key);
      free(b);
      return NULL;
    }else if(b->left != NULL && b->right != NULL){/* Two children*/
      /*printf("Entering two child delete routine\n");*/

      /*Finds the left most child of right child*/
      temp = b->right;
      while (temp->left != NULL){
	temp = temp->left;
      }
      
      /*printf("found leftmost child of right tree\n");*/
      /*printf("%s, tempkey\n",temp->key);*/
      /*
	if (temp->right ==NULL){
	strcpy(b->key,temp->key);
	b = rbt_delete(b,temp->key);
	free(temp->key);
	free(temp);
	return b;
	}else{
      */
	    
      /*must use temp key so not deleting two values;*/
      temp_string = emalloc((strlen(temp->key)+1)*sizeof temp_string[0]);

      strcpy(temp_string,temp->key);
      /*printf("%s, temp_string\n", temp_string);*/
      b = rbt_delete(b,temp->key);
      free(b->key);
      b->key = emalloc((strlen(temp_string)+1)*sizeof temp_string[0]);
      strcpy(b->key,temp_string);
      free(temp_string);
      return b;

      /*if last left a leaf node do a simple swap*/
      /*copy the key.*/
      /* if it has a right child
       * copy the value of the key
       * delete the node calling by key name*/ 
      
	
    }else if(b->left != NULL && b->right == NULL){/*left child only*/
      temp = b->left;
      free(b->key);
      free(b);
      return temp;
    }else {
      /*if (b->left ==NULL && b->right != NULL){*//*right child only*/
      temp = b->right;
      free(b->key);
      free(b);
      return temp;
    }
      
  }else if (comparision >0){
    if (b->right ==NULL){
      return b;
    }else{
      b->right = rbt_delete(b->right,str);
      return b;
    }
  }else{
    if (b->left ==NULL){
      return b;
    }else{
      b->left= rbt_delete(b->left,str);
      return b;
    }
  }
}

rbt rbt_free(rbt b){
  while (b != NULL){
    b = rbt_delete(b,b->key);
  }
  return b;
}

rbt right_rotate(rbt r){
  rbt temp;
  if (r ==NULL||r->left==NULL){
    return r;
  }
  temp = r;
  r = temp->left;
  temp->left = r->right;
  r->right = temp;
  return r;
}

rbt left_rotate(rbt r){
  rbt temp;
  if(r==NULL|| r->right==NULL){
    return r;
  }
  temp = r;
  r = temp->right;
  temp->right = r->left;
  r->left=temp;
  return r;
}
