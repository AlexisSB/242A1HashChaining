#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>

#include "mylib.h"
#include "container.h"
#include "flexarray.h"
#include "htable.h"
#include "rbt.h"

/* Default size for hash table*/
#define DEFAULT_SIZE 3877
/* Default container type for hash table*/
#define DEFAULT_TYPE FLEX_ARRAY

enum print_option {PRINT, DONT_PRINT};

/*
 * Prints a help message to stderr describing use of this program.
 * Help message contains information on command line options.
 * Message contained in error_message.txt.
 */
void print_help_message(){
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

/*
 * Main program takes in two groups of words.
 * The first group is taken from a file given as an arguement.
 * The words from the first group are inserted into a hashtable.
 * The hash table uses either a dynamic array or a red black tree to store words.
 * The second group of words is taken from stdin.
 * Words that occur in the second group but not the first are printed to stdout.
 * Options:
 *     -h         print help message
 *     -i         print timing info
 *     -s size    change size of hashtable
 *     -r         use red black tree to store values (default flexarray)
 *     -p         print contents of hash table, doesn't take input from stdin.
 */
int main(int argc, char **argv) {
    FILE *infile;
    htable h;
    char word[256];
    
    /*Set default size and type for hashtable*/
    int h_table_size = DEFAULT_SIZE;
    container_t container_type = DEFAULT_TYPE;
    
    /* Set default no printing of hashtable and timing info*/
    enum print_option print_hash_table = DONT_PRINT;
    enum print_option print_time_info = DONT_PRINT;
    
    /*Variables for timing info*/
    clock_t start_insert,finish_insert;
    clock_t start_search, finish_search;
    double  insert_time, search_time;
    int unknown_word_counter = 0;

    /*Option handling variables*/
    const char *optstring = "rs:pih";
    char option;

    /*Option handling*/
    while ((option = getopt(argc,argv,optstring))!=EOF){
        switch(option){
            case 'r':
                /*use red-black tree as container*/
                /*printf("Option : %c\n",option);*/
                container_type = RED_BLACK_TREE;
                break;
            case 's' :
                /*Change hash table size*/
                /*printf("Option : %c\n",option);*/
                h_table_size = atoi(optarg);
                
                if (h_table_size ==0){
                    fprintf(stderr,
                            "Error: Hash table size not set or set to 0\n");
                    exit(EXIT_FAILURE);
                }
                printf("Htable size = %d\n", h_table_size);
                break;
            case 'p' :
                /*print to stdout*/
                /*printf("Option : %c\n",option);*/
                print_hash_table = PRINT;
                break;
            case 'i' :
                /*print timing information*/
                /*printf("Option : %c\n",option);*/
                print_time_info = PRINT;
                break;
            case 'h':
                /*print help message*/
                /*printf("Option : %c\n",option);*/
                print_help_message();
                exit(EXIT_SUCCESS);
                break;
            default:
                /*print error then usage message*/
                /*printf("default\n");*/
                print_help_message();
                exit(EXIT_SUCCESS);
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
	    
            if (print_time_info == PRINT){ /*Print insert timing*/
                insert_time = (double)(finish_insert-start_insert)/(double)CLOCKS_PER_SEC;
                fprintf(stderr, "Fill time:\t%.6f\n", insert_time);
                search_time = (double)(finish_search-start_search)/(double)CLOCKS_PER_SEC;
                fprintf(stderr, "Search time:\t%.6f\n", search_time);
                fprintf(stderr, "Unknown words:\t%d\n", unknown_word_counter);  
            }
        }
	  
        /*printf("Starting free\n");*/
        htable_free(h);
        fclose(infile);
        return EXIT_SUCCESS;
    }else{
        fprintf(stderr, "Error: Please include name of file in arguements\n");
        return EXIT_FAILURE;
    }
  
}
        
