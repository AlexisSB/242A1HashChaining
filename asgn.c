#include <stdio.h>
#include <stdlib.h>

#include <getopt.h>
#include "mylib.h"
#include "container.h"
#include "flexarray.h"
#include "htable.h"
#include "rbt.h"

#define DEFAULT_SIZE 3877

int main(int argc, char **argv) {
  FILE *infile;
  htable h;
  char word[256];
  int h_table_size = DEFAULT_SIZE;

  const char *optstring = "rs:pih";
  char option;

  /* optarg global variable for argument*/

  while ((option = getopt(argc,argv,optstring))!=EOF){
      switch(option){
          case 'r':
              /*use red-black tree as container*/
              printf("Option : %c\n",option);
              
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
              break;
          case 'i' :
              /*print timing information*/
              printf("Option : %c\n",option);
              break;
          case 'h':
              /*print help message*/
              printf("Option : %c\n",option);
              break;
              /*
          case '?':
              if (optopt == 's'){
                  fprintf(stderr, "Option -%c requires an arguement. \n", optopt);
              }else{
              */
              /*print error then usage message*/
              /*
                  break;
      }
      */
          default:
              /*print error then usage message*/
              printf("default");
              break;
      }
  }
             
  /*optind should now point to index of non-option argument in argv*/
  
  if (argv[optind] != NULL){
    if (NULL ==(infile = fopen(argv[optind],"r"))){
      fprintf(stderr,"%s: can't find file %s\n", argv[0],argv[optind]);
	return EXIT_FAILURE;
    }

    h = htable_new(h_table_size);
    /*Fill hash table up with words from file*/
    while (getword(word, sizeof word, infile)!= EOF){
      htable_insert(h,word);
    }

    /* Take words in from stdin*/
    while ((getword(word,sizeof word, stdin)!=EOF)){
      if (!(htable_search(h,word))){
	printf("%s\n",word);
      }
    }
    /*htable_print(h,stdout);*/
    htable_free(h);

    fclose(infile);
  
    return EXIT_SUCCESS;
  }else{
      fprintf(stderr, "Error: Please include name of file in arguements\n");
    return EXIT_FAILURE;
  }
  
}
        
