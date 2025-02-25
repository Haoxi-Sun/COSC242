/**
 * @file htable.c
 * functions for COSC242 Assignment.
 * Generates a hash table.
 *
 * Author: Elsie Sun, Grace Jan, Xiaoqian Yan.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "htable.h"
#include "mylib.h"


/**
 * Declares the functions did not specify in htable.h ,
 * and those functions are written at the end of file, 
 * so declares them at top to allow other functions to call them.
 */
static unsigned int htable_word_to_int(char *word);
static unsigned int htable_step(htable h, unsigned int i_key);
static void print_stats_line(htable h, FILE *stream, int percent_full);


/**
 * Speficy the structure of the hash table.
 */
struct htablerec{
    int capacity;      /* number of items can fit in the hash table.  */
    char **keys;       /* keys in the hash table */
    int num_keys;      /* number of keys in the hash table right now. */
    int *freqs;        /* number of times we have repeatedly inserted each key */
    int *stats;        /* records the statistics as the table builds. */
    hashing_t types;   /* the type of collision resolution strategy. */
};


/**
 * deallocates memory when we do not need to use the pointer
 * we had allocated with malloc 
 * 
 * @param h - the hash table.
 */
void htable_free(htable h){
    int i;
    for(i=0; i<h->capacity; i++){
        free(h->keys[i]);
    }
    free(h->keys);
    free(h->freqs);
    free(h->stats);
    free(h);
}

/**
 * Inserts a key into the hash table.
 *
 *There are three possibilities when the hash table isn't full
 *
 * First  : if nothing at the position in the hash tbale
 *        - insert the string at the index and return 1
 *
 * Second : same string is at the position
 *        - increment the frequency of the index and return the frequency  
 *
 * Third  : different string is at the position
 *         - depends on resolution strategy and
 *           increment the number of collision
 *
 * @param h - the hash table.
 * @param str - the key/ string we want to insert.
 * @return the frequency of the hash table or (1 or 0)
 * (0: when the hash table is full or 1: nothing at the index trying to insert. 
 */
int htable_insert(htable h, char *str){
    /* calculates the step before searching. */
    int step = htable_step(h, htable_word_to_int(str));
    /* the index of the hash table. */ 
    int index = htable_word_to_int(str) % h->capacity;
    /* initialises the number of collision. */
    int collision = 0; 

    /* if number of collision equal the capacity of hash table means
       the tbale is full */
    while(collision < h->capacity){

        /*if nothing is in the index of hash table,
          copy the key into the index and return 1*/
        if(h->keys[index]== NULL){
            h->keys[index] = emalloc((strlen(str)+1) * sizeof h->keys[0][0]);
            strcpy(h->keys[index],str);
            h->freqs[index] = 1;
            h->stats[h->num_keys] = collision;
            h->num_keys += 1;
            return 1;
            
            /*if the key is same as the key at the index of table,
             increases the frequency of the position by 1*/
        }else if(strcmp(h->keys[index],str)==0){
            h->freqs[index] += 1;
            return h->freqs[index];
            
           /*if the key in the index in different to the key you want to insert,
              try the collision resolution strategy*/
        }else{
            if(LINEAR_P == h->types) index = (index+1) % h->capacity;
            else if(DOUBLE_H == h->types) index = (index+step) % h->capacity;
        }
        collision++;
    }
    
    /* when the hash table is full. */
    return 0;
}


/**
 * creates a new hash table 
 *
 * @param capacity - the size of the hash table.
 * @param types - resolution when face the collision.
 * @return the new hash table.
 */
htable htable_new(int capacity , hashing_t types){
    int i;
    /* declares the hash table and allocates its  memory. */
    htable table = emalloc(sizeof *table);

    /* initialises the resolution strategy, whether it is linear or double. */
    table->types = types;

    /* initialises the  capacity of hash table. */
    table->capacity = capacity;

    /* initialises number of keys of hash table*/
    table->num_keys = 0;

    /* allocates the memory of frequency array */
    table->freqs = emalloc(table->capacity * sizeof table->freqs[0]);

    /* allocates the memory of keys array*/
    table->keys = emalloc(table->capacity * sizeof table->keys[0]);

    /* allocates the memory of stats arrat  */
    table->stats = emalloc(table->capacity * sizeof table->stats[0]); 

    /* sets the initial values for its key, frequency and statistics. */
    for(i=0; i<table->capacity; i++){
        table->keys[i] = NULL;
        table->freqs[i] = 0;
        table->stats[i] = 0;
    }
    return table;
}

/**
 * prints out each key with  its frequency.
 *
 * @param h - the hash table.
 * @param stream - the stream to print data to.
 */

void htable_print(htable h, FILE *stream){
    int i;
    for(i=0;i<h->capacity;i++){
        if(h->freqs[i] != 0){
            fprintf(stream, "%-4d %s\n",h->freqs[i],h->keys[i]);
        }
    }
}

/**
 * checks the spelling of words.
 *
 * @param h - the hash table.
 * @param filename - the text file that we want to check the spelling of.
 * @return unknown words.
 */
int htable_spell_check(htable h, char *filename){
    char word[256];
    int unknown_words = 0;
    FILE *file = fopen(filename, "r");

    if(NULL == file){
        fprintf(stderr, "File is not found.\n");
        exit(EXIT_FAILURE);
    }
    /* while the input is from a standard input*/
    while(getword(word, sizeof word, stdin) != EOF){
        htable_insert(h, word);
    }
    /* while the input is from a file*/
    while(getword(word, sizeof word, file) != EOF){
        if(htable_search(h, word) == 0){
            fprintf(stdout,"%s\n", word);
            unknown_words++;
        }
    }
    fclose(file);
    return unknown_words;
}

/**
 * searches the key in the hash table and
 * if the key at the position is not the key  we want to search
 * then undergo a search based on their resolution strategy.
 *
 * @param h - the hash table.
 * @param str - the string we want to search
 * @return the frequency of the position or 0
 * when the table doesn't contain the key.
 */
int htable_search(htable h, char *str){
    int step = htable_step(h, htable_word_to_int(str));
    int collisions = 0;
    int index = htable_word_to_int(str) % h->capacity;

    /* while there is an item at that position. */
    while(h->keys[index] != NULL){

        /* if the key at the position is equal to what we want to find
           return the frequency of the position*/
        if(strcmp(h->keys[index],str)==0){
            return h->freqs[index];
        }
        /* the item at this position is not the key,
         search the key depends on its resolution strategy*/
        if(h->types == LINEAR_P) index = (index+1) % h->capacity;
        if(h->types == DOUBLE_H) index = (index+step) % h->capacity;
        collisions++;
    
        /* the hash table was full but did not contain the key. */
        if(collisions == h->capacity) return 0;
    }
    /*the hash table did not contain the key when the table is not full*/
    return 0;
}
/**
 * prints the entire contents of the hash table.
 *
 * @param h - the hash table.
 * @param stream - the stream to print data to.
 */
void htable_print_entire_table(htable h, FILE *stream){
    int i;
    fprintf(stream, "Pos   Freq   Stats   Word \n");
    fprintf(stream, "--------------------------\n");
    for(i=0; i<h->capacity; i++){
        if(h->keys[i] != NULL){
            fprintf(stream, "%5d %5d %5d   %s\n",
                    i, h->freqs[i], h->stats[i], h->keys[i]);
        }else{
            fprintf(stream,"%5d %5d %5d   %s\n",
                    i, h->freqs[i], h->stats[i], "");
        }
    }
}

/**
 * Prints out a table showing what the following attributes were like
 * at regular intervals (as determined by num_stats) while the
 * hashtable was being built.
 *
 * @li Percent At Home - how many keys were placed without a collision
 * occurring.
 * @li Average Collisions - how many collisions have occurred on
 *  average while placing all of the keys so far.
 * @li Maximum Collisions - the most collisions that have occurred
 * while placing a key.
 *
 * @param h the hashtable to print statistics summary from.
 * @param stream the stream to send output to.
 * @param num_stats the maximum number of statistical snapshots to print.
 */
void htable_print_stats(htable h, FILE *stream, int num_stats) {
    int i;

    fprintf(stream, "\n%s\n\n", 
            h->types == LINEAR_P ? "Linear Probing" : "Double Hashing"); 
    fprintf(stream, "Percent   Current    Percent    Average      Maximum\n");
    fprintf(stream, " Full     Entries    At Home   Collisions   Collisions\n");
    fprintf(stream, "------------------------------------------------------\n");
    for (i = 1; i <= num_stats; i++) {
        print_stats_line(h, stream, 100 * i / num_stats);
    }
    fprintf(stream, "------------------------------------------------------\n\n");
}

/**
 * Prints out a line of data from the hash table to show the state of
 * the table was at when it was at certain percentage full.
 * Note: If the hashtable is less full than percent_full then no data
 * will be printed.
 *
 * @param h - the hash table.
 * @param stream - a stream to print the data to.
 * @param percent_full - the point at which to show the data from.
 */
static void print_stats_line(htable h, FILE *stream, int percent_full) {
    int current_entries = h->capacity * percent_full / 100;
    double average_collisions = 0.0;
    int at_home = 0;
    int max_collisions = 0;
    int i = 0;

    if (current_entries > 0 && current_entries <= h->num_keys) {
        for (i = 0; i < current_entries; i++) {
            if (h->stats[i] == 0) {
                at_home++;
            } 
            if (h->stats[i] > max_collisions) {
                max_collisions = h->stats[i];
            }
            average_collisions += h->stats[i];
        }
    
        fprintf(stream, "%4d %10d %11.1f %10.2f %11d\n", percent_full, 
                current_entries, at_home * 100.0 / current_entries,
                average_collisions / current_entries, max_collisions);
    }
}

/**
 * converts a string to an integer.
 *
 * @param word - the key.
 * @return an integer that is the position of the key.
 */
static unsigned int htable_word_to_int(char *word){
    unsigned int result = 0;

    while(*word != '\0'){
        result = (*word++ + 31 *result);
    }
    return result;
}

/**
 * calculates a "step" before beginning to search the keys array.
 *
 * @param h - the hash table.
 * @param i_key - the integer that from a string.
 * @return the next position.
 */
static unsigned int htable_step(htable h, unsigned int i_key){
    return 1 + (i_key % (h->capacity-1));
}
