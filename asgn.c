#include <stdio.h>
#include <stdlib.h>

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

  if (argc > 1){
    if (NULL ==(infile = fopen(argv[1],"r"))){
      fprintf(stderr,"%s: can't find file %s\n", argv[0],argv[1]);
	return EXIT_FAILURE;
    }

    h = htable_new(DEFAULT_SIZE);
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
    printf("Wrong number of arguments, please include in file");
    return EXIT_FAILURE;
  }
  
}
        
