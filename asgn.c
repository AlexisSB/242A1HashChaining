#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <getopt.h>
#include "mylib.h"
#include "container.h"
#include "flexarray.h"
#include "htable.h"
#include "rbt.h"

#define DEFAULT_SIZE 3877
#define DEFAULT_TYPE FLEX_ARRAY

enum print_option {PRINT, DONT_PRINT};

void print_error_message(){
  FILE *helpfile;
  char input[255];
  char *status;

  helpfile = fopen("error_message.txt","r");

  if(helpfile ==NULL){
    fprintf(stderr, " Can't find help file\n");
  }else{
    status = fgets(input, sizeof(input), helpfile);
    while (status){
      fprintf(stderr,"%s", input);
      status = fgets(input, sizeof(input), helpfile);
    }
  }
}

int main(int argc, char **argv) {
     FILE *infile;
     htable h;
     char word[256];
     int h_table_size = DEFAULT_SIZE;
     container_t container_type = DEFAULT_TYPE;
     enum print_option print_hash_table = DONT_PRINT;
     enum print_option print_time_info = DONT_PRINT;
     clock_t start_insert,finish_insert;
     clock_t start_search, finish_search;
     double  insert_time, search_time;
     const char *optstring = "rs:pih";
     char option;
     int unknown_word_counter = 0;

     /* optarg global variable for argument*/

     while ((option = getopt(argc,argv,optstring))!=EOF){
	  switch(option){
          case 'r':
	       /*use red-black tree as container*/
	       printf("Option : %c\n",option);
	       container_type = RED_BLACK_TREE;
	       break;
          case 's' :
	       /*optarg is the table size*/
	       /*Need error check for option if no following opt arg*/
	       printf("Option : %c\n",option);
	       h_table_size = atoi(optarg);
	       printf("Htable size = %d\n", h_table_size);
	       break;
          case 'p' :
	       /*print to stdout*/
	       printf("Option : %c\n",option);
	       print_hash_table = PRINT;
	       break;
          case 'i' :
	       /*print timing information*/
	       printf("Option : %c\n",option);
	       print_time_info = PRINT;
	       break;
          case 'h':
	       /*print help message*/
	       printf("Option : %c\n",option);
	       print_error_message();
	       exit(EXIT_SUCCESS);
	       break;
          default:
	       /*print error then usage message*/
	       printf("default");
	       break;
	  }
     }
             
     /*optind should now point to index of non-option argument in argv*/
     /*Open file and check if it can be opened*/
     if (argv[optind] != NULL){
	  if (NULL ==(infile = fopen(argv[optind],"r"))){
	       fprintf(stderr,"%s: can't find file %s\n", argv[0],argv[optind]);
	       return EXIT_FAILURE;
	  }
	  
	  /*Make the new hash table*/
	  h = htable_new(h_table_size,container_type);
    
	  /*Fill hash table up with words from file*/
	  start_insert = clock();
	  while (getword(word, sizeof word, infile)!= EOF){
	       htable_insert(h,word);
      	  }
	  finish_insert = clock();
    
	  if (print_hash_table == PRINT){
	       htable_print(h,stdout);
	       /*variables set to stop compiler warning ask demo???*/
	       start_search = 0;
	       finish_search = 0;
	  }else{
	       /* Take words in from stdin*/
	       /* Search for input words in the hashtable*/
	       start_search = clock();
	       while ((getword(word,sizeof word, stdin)!=EOF)){
		    if (!(htable_search(h,word))){
			 printf("%s\n",word);
			 unknown_word_counter++;
		    }
	       }
	       finish_search = clock();
	       
	  }
	  
	  if (print_time_info == PRINT){
	       /*Print insert timing*/
	       insert_time = (double)(finish_insert-start_insert)/(double)CLOCKS_PER_SEC;
	       fprintf(stderr, "Fill time:\t%.6f\n", insert_time);
	       if (print_hash_table == DONT_PRINT){
		    search_time = (double)(finish_search-start_search)/(double)CLOCKS_PER_SEC;
		    fprintf(stderr, "Search time:\t%.6f\n", search_time);
		    fprintf(stderr, "Unknown words:\t%d\n", unknown_word_counter);  
	       }
	  }	       
	  
	  /*htable_print(h,stdout);*/
	  /*printf("Starting free\n");*/
	  htable_free(h);

	  fclose(infile);
  
	  return EXIT_SUCCESS;
     }else{
	  fprintf(stderr, "Error: Please include name of file in arguements\n");
	  return EXIT_FAILURE;
     }
  
}
        
