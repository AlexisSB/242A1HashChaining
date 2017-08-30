#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "mylib.h"

/* Full debug memory allocation with error checking.
 * Checks for succesful allocation.
 * Checks for zero length allocation.
 * Activated with #define MALLOC_DEBUG in header file.
 * @param line - line number
 * @param file - file name
 * @param size - memory size to allocate.
 * @return void pointer to start of allocated memory.
 */
void *do_debug_emalloc(long line, char *file, size_t size){
  void *result;
  printf("%s(%ld): log, malloc(%d)\n", file, line, (int)size);
  
  if (size ==0){
    fprintf(stderr, "Zero length allocation\n");
    exit(EXIT_FAILURE);
  }else{
    result = malloc(size);
    if(NULL == result){
      fprintf(stderr, "Memory allocation fault\n");
      exit(EXIT_FAILURE);
    }
    return result;
  }
}

/* Vanilla memory allocation with error checking.
 * @param size - memory size to allocate.
 * @return void pointer to start of allocated memory. 
 */
void *do_normal_emalloc(size_t size){
  void *result;
  result = malloc(size);
  if(NULL == result){
    fprintf(stderr, "Memory allocation fault\n");
    exit(EXIT_FAILURE);
  }
  return result;
}


void *erealloc(void *p, size_t s){
  void *result = realloc(p,s);
  if(NULL == result){
    fprintf(stderr, "Memory Allocation Fault\n");
    exit(EXIT_FAILURE);
  }
  return result;
}

/* Insertion sort.
 * In place, O(n^2). 
 * Algorithm based on COSC242 Lecture 1 slides.
 * @param a - the array to sort
 * @param n - the size of the array
 */
void insertion_sort(int *a,int n){
  int i,j;
  int temp;
  for(i=1;i<n;i++){
    temp = a[i];
    j=i-1;
    while(j>=0 && a[j]>temp){
      a[j+1] = a[j];
      j=j-1;
      a[j+1] = temp;
    }
  }
}

/* Merge.
 * Takes two sorted halves of a array and merges it
 * into a single sorted array.
 * Uses workspace to copy values into it.
 * @param array - source and destination for sorted halves.
 * @param workspace - workspace for copy and sort.
 * @param len - total length of array. 
 */
void merge(int *array, int *workspace, int len){
  int left_half = 0;
  int right_half = len/2;
  int w = 0;
  int i;
  /*Finds smallest value from left or right array*/
  while ((left_half<(len/2))&&right_half<len){
    if(array[left_half]<=array[right_half]){
      workspace[w] = array[left_half];
      left_half++;
      w++;
    }else{
      workspace[w] = array[right_half];
      right_half++;
      w++;
    }
  }
  /* When all values taken from one half,
   * adds the rest of the other to the array*/
  if(left_half>=(len/2)){
    while(right_half<len){
      workspace[w]= array[right_half];
      w++;
      right_half++;
    }
  }else{
    while(left_half<(len/2)){
      workspace[w]= array[left_half];
      w++;
      left_half++;
    }
  }

  for (i=0;i<len;i++){
    array[i]=workspace[i];
  }

}
               

/* Merge Sort.
 * Drops to insertion sort when array size small enough.
 * Recursive.
 * @param array - the array to sort
 * @param len - the size of the array
 * @param workspace - the workspace used for sorting, equal length to array.
 */
void merge_sort(int *array,int len,int *workspace){
  int mid;
  int drop_value = 40;
  if (len<2){
    return;
  }
  if (len < drop_value){
    insertion_sort(array,len);
  }else{
    mid = len/2;
    /*printf("%d\n",mid);*/
    merge_sort(array,mid,workspace);
    merge_sort(array+mid,len-mid,workspace+mid);
    merge(array,workspace,len);     
  }
}

/*Recursive print method for an array*/
void print_array(int *a, int n){
  if(n>0){
    printf("%d\n",a[0]);
    print_array(a+1,n-1);
  }
}

/* Find median of three values.
 * Used for pivot select in quicksort.
 * Uses insertion sort of three values then picks the middle one.
 * A bit of a hack but should be constant time.
 * @param one - first value
 * @param two - second value
 * @param three - third value
 * @return int median of three values.
 */
int median_of_three(int one, int two, int three ){
  int pivots[3];
  pivots[0] = one;
  pivots[1]= two;
  pivots[2] = three;
  insertion_sort(pivots,3);
  /*print_array(pivots,3);
    printf("%d\n", pivots[1]);*/
  return pivots[1];
}

/* Quicksort, in place, average O(nlogn) sort.
 * Recursive partitioning.
 * Uses median of three to find pivot.
 * Drops to insertion sort at small array size.
 * @param array - array to be sorted
 * @param size - size of array.
 */
void quick_sort(int *array, int size){
  int pivot;
  int first,mid,last;
  int i;
  int j;
  int temp;
  int dropvalue = 47;
   
  if (size < 2){
    return;
  }else{
        
    if (size<dropvalue){
      insertion_sort(array,size);
    }else{
             
      first = array[0];
      mid  = array[size/2];
      last = array[size-1];
      pivot = median_of_three(first,mid,last);
          
      i = 0-1;
      j = size;
      for (;;){
	do{
	  i++;
	}while(array[i]<pivot);

	do{
	  j--;
	}while(array[j]>pivot);

	if (i<j){
	  temp = array[i];
	  array[i] = array[j];
	  array[j] = temp;
	}else{
	  break;
	}
      }
      /*printf("%d,%d\n",i,j);*/
      quick_sort(array,j+1);
      quick_sort(&array[j+1], size-j-1);

    }
  }
    
}

/* From lab book may want to get clarification*/
int getword(char *s, int limit, FILE *stream){
  int c;
  char *w = s;
  /*Tests to make sure everything set up properly*/
  assert(limit >0 && s != NULL && stream != NULL);

  /* skip to the start of the word */
  while (!isalnum(c = getc(stream)) && EOF != c);
    
  if (EOF == c) {
    return EOF;
  } else if (--limit > 0) { /* reduce limit by 1 to allow for the \0 */
    *w++ = tolower(c);
  }
  while (--limit > 0) {
    if (isalnum(c = getc(stream))) {
      *w++ = tolower(c);
    } else if ('\'' == c) {
      limit++;
    } else {
      break;
    }
  }
  *w = '\0';
  return w - s;
}





