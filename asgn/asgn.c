/**
 * @file asgn.c
 * this is a main file foe COSC242 Assignment.
 * @author Elsie Sun, Grace Jan, Xiaoqian Yan.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <time.h>
#include "mylib.h"
#include "htable.h"

/* declares the boolean data type. */
typedef enum bool_e {FALSE, TRUE} boolean;
/*declares the functions which are written at the end of the file*/
static void usage_message(char *file);
static int prime_number(int num);
static int is_prime(int num);
static void boolean_choose(int argc, char **argv,hashing_t *type, 
                           boolean *entire_table, boolean *print_stats,
                           boolean *spell_checking, int *snapshots,
                           int *tablesize, char **filename);

/**
 * The main function of the program.
 *
 * @param argc - the first group of words which reads from stdin
 *               and put them into the hash table.
 * @param argv - the second group of words readsfrom the file
 specified on the command line.
 @ @return EXIT_SUCCESS.
*/
int main(int argc, char **argv){
    /* initializes the variables. */
    boolean entire_table = FALSE, print_stats = FALSE, spell_checking = FALSE;
    int snapshots = 0, tablesize = 0, unknown_words = 0;
    clock_t start, end, start_search, end_search;
    htable h;
    char *filename = '\0';
    char word[256];
    hashing_t type = LINEAR_P;


    boolean_choose(argc, argv, &type, &entire_table,
                   &print_stats, &spell_checking,
                   &snapshots, &tablesize, &filename);
    
    /* creates a hash table.*/
    h = htable_new(tablesize, type);

    /* start to time how long it takes to insert the words into the hash table */
    start = clock();
    while(getword(word, sizeof word, stdin) != EOF){
        htable_insert(h, word);
    }
    end = clock();

    /* if entire_table is TRUE, prints entire table. */
    if(entire_table){
        htable_print_entire_table(h, stderr);
    }

    /* if spell_checking is TRUE, times how long it takes to insert the words
       and how long it takes to search the word, and print the unknown words.*/
    if(spell_checking){
        start_search = clock();
        unknown_words = htable_spell_check(h, filename);
        end_search = clock();

        fprintf(stderr, "Fill time     : %.6f\n",
                (end-start)/(double)CLOCKS_PER_SEC);
        fprintf(stderr, "Search time   : %.6f\n",
                (end_search-start_search)/(double)CLOCKS_PER_SEC);
        fprintf(stderr, "Unknown words = %d\n", unknown_words);
    }
    /* if print_stats is TRUE, prints stats*/
    else if(print_stats){
        htable_print_stats(h, stdout, snapshots);
    }else{
        htable_print(h,stderr);
    }

    /* deallocates the memories of htable and  file. */
    htable_free(h);
    free(filename);
    return EXIT_SUCCESS;
}

/**
 * The prime_number is get the size of a hash table.
 *
 * @param num - the size of a hash table.
 * @return the first prime number as the size.
 */
static int prime_number(int num){
    while(1){
        if(is_prime(num)) return num;
        num++;
    }
}

/**
 * Checks if num is prime.
 *
 * @param num - a number need to be checked.
 * @return 1 is num is the prime number, else return 0;
 */
static int is_prime(int num){
    int i;
    if(num == 2) return 1;
    if(num % 2 == 0) return 0;

    for(i=3; i<num; i++){
        if(num % i == 0) return 0;
    }
    return 1;
}

/**
 * Prints the message
 * when the program is given the -h option
 * or an invalid option is given.
 *
 * @param filename - the file name.
 */
static void usage_message(char *filename){
    fprintf(stderr,"Usage: %s [OPTION]... <STDIN>\n", filename);
    fprintf(stderr,"\n");
    fprintf(stderr,"Perform various operations using a hash table.  ");
    fprintf(stderr,"By default, words are\nread from stdin ");
    fprintf(stderr,"and added to the hash table, before being printed out\n");
    fprintf(stderr,"alongside their frequencies to stdout.\n");
    fprintf(stderr,"\n");
    fprintf(stderr," -c FILENAME  Check spelling of words in FILENAME using ");
    fprintf(stderr,"words \n              from stdin as dictionary.  ");
    fprintf(stderr,"Print unknown words to\n");
    fprintf(stderr,"              stdout, timing info & count to stderr ");
    fprintf(stderr,"(ignore -p)\n");
    fprintf(stderr," -d           Use double hashing ");
    fprintf(stderr,"(linear probing is the default)\n");
    fprintf(stderr," -e           Display entire contents of hash table ");
    fprintf(stderr,"on stderr\n");
    fprintf(stderr," -p           Print stats info instead of frequencies & ");
    fprintf(stderr,"words\n");
    fprintf(stderr," -s SNAPSHOTS Show SNAPSHOTS stats snapshots ");
    fprintf(stderr,"(if -p is used)\n");
    fprintf(stderr," -t TABLESIZE Use the first prime >= TABLESIZE as");
    fprintf(stderr,"htable size\n");
    fprintf(stderr,"\n");
    fprintf(stderr," -h           Display this message\n");
    fprintf(stderr,"\n");
}

/**
 * Assigns values to these variables.
 *
 * @param argc - the first group of words read from stdin
 *        -> put into the hash table.
 * @param argv - the second group of words read from the file
 *        -> specified on the command line.
 * @param type - a collision resolution strategy.
 * @param entire_table - to be TURE, when the program is given the -e option.
 * @param print_stats - to be TURE, when the program is given the -p option.
 * @param spell_checking - to be TURE, when the program is given the -c option.
 * @param snapshots - stats snapshots.
 * @param tablesize - size of the hash table.
 * @param filename -  -> the textfile that we want to check the spelling in.
 */
static void boolean_choose(int argc, char **argv, hashing_t *type,
                           boolean *entire_table, boolean *print_stats,
                           boolean *spell_checking, int *snapshots, int *tablesize,
                           char **filename){

    const char *optstring = "c:deps:t:h";
    char option;
    *tablesize = 113;
    *snapshots = 10;

    while((option = getopt(argc, argv, optstring)) != EOF){
        switch(option){
            case 'c':
                *spell_checking = TRUE;
                *filename = emalloc((strlen(optarg)+1) * sizeof *filename[0]);
                strcpy(*filename, optarg);
                break;
            case 'd':
                *type = DOUBLE_H;
                break;
            case 'e':
                *entire_table = TRUE;
                break;
            case 'p':
                *print_stats = TRUE;
                break;
            case 's':
                *snapshots = atoi(optarg);
                break;
            case 't':
                *tablesize = prime_number(atoi(optarg));
                break;
            case 'h':
            default:
                usage_message(argv[0]);
                exit(EXIT_SUCCESS);
        }
    }

}
