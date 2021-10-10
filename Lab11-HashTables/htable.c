/**
 * @file htable.c
 * functions for COSC242 Assignment.
 * Generates a hash table.
 *
 * Author: Elsie Sun, Grace Zhan, Xiaoqian Yan.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "htable.h"
#include "mylib.h"

/* declares the htable_word_to_int function. */
static unsigned int htable_word_to_int(char *word);
/* declares the htable_step function. */
static unsigned int htable_step(htable h, unsigned int i_key);
/* declares the print_stats_line function. */
static void print_stats_line(htable h, FILE *stream, int percent_full);

/**
 * The structure of the hash table.
 */
struct htablerec{
    int capacity; /* number of items in the hash table. */
    char **keys; /* keys in the hash table. */
    int num_keys; /* number of keys in the hash table. */
    int *freqs; /* frequency of each keys. */
    int *stats; /* records statistics as the table builds. */
    hashing_t types; /* a collision resolution strategy. */
};

/**
 * deallocates memory of the hash table.
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
 * inserts a key into the hash table.
 *
 * @param h - the hash table.
 * @param str - the key.
 * @return the frequency of the hash table or 0.
 */
int htable_insert(htable h, char *str){
    int step = htable_step(h, htable_word_to_int(str)); /* calculates a step before beginning to seach. */
    int index = htable_word_to_int(str) % h->capacity; /* the index of the hash table. */ 
    int collision = 0; /* initialises the collision. */

    while(collision < h->capacity){
        if(h->keys[index]== NULL){
            h->keys[index] = emalloc((strlen(str)+1) * sizeof h->keys[0][0]);
            strcpy(h->keys[index],str);
            h->freqs[index] = 1;
            h->stats[h->num_keys] = collision;
            h->num_keys += 1;
            return 1;
        }else if(strcmp(h->keys[index],str)==0){
            h->freqs[index] += 1;
            return h->freqs[index];
        }else{
            if(LINEAR_P == h->types) index = (index+1) % h->capacity;
            else if(DOUBLE_H == h->types) index = (index+step) % h->capacity;
        }
        collision++;
    }
    /* if the string is not in the hash table. */
    return 0;
}

/**
 * creates a new hash table with its type.
 *
 * @param capacity - the size of the hash table.
 * @param types - resolute the collision.
 * @return the new hash table.
 */
htable htable_new(int capacity , hashing_t types){
    int i;
    htable table = emalloc(sizeof *table); /* declares the hash table and allocates memory. */
    table->types = types; /* initialises the hash table's type, that is linear or double. */
    table->capacity = capacity; /* initialises the hash table's capacity. */
    table->num_keys = 0; /* initialises the hash table's number of keys. */
    table->freqs = emalloc(table->capacity * sizeof table->freqs[0]); /* allocates the hash table's frequency array. */
    table->keys = emalloc(table->capacity * sizeof table->keys[0]); /* allocates the hash table's keys array. */
    table->stats = emalloc(table->capacity * sizeof table->stats[0]); /* allocates the hash table's stats array. */

    /* sets the initial values for each key, frequency and statistics. */
    for(i=0; i<table->capacity; i++){
        table->keys[i] = NULL;
        table->freqs[i] = 0;
        table->stats[i] = 0;
    }
    return table;
}

/**
 * prints out the key and its frequency.
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
 * @param filename - takes 'filename' to be the text file that we want to check the spelling in.
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

    while(getword(word, sizeof word, stdin) != EOF){
        htable_insert(h, word);
    }
    
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
 * searches the key in the hash table.
 *
 * @param h - the hash table.
 * @param str - the key.
 * @return the frequency of the position.
 */
int htable_search(htable h, char *str){
    int step = htable_step(h, htable_word_to_int(str));
    int collisions = 0;
    int index = htable_word_to_int(str) % h->capacity;

    /* while there is an item at that position. */
    while(h->keys[index] != NULL){
        if(strcmp(h->keys[index],str)==0){
            return h->freqs[index];
        }
        /* the item at this position is not the key. */
        if(h->types == LINEAR_P) index = (index+1) % h->capacity;
        if(h->types == DOUBLE_H) index = (index+step) % h->capacity;
        collisions++;
    
        /* the hash table was full but did not contain our key. */
        if(collisions == h->capacity) return 0;
    }
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
            fprintf(stream, "%5d %5d %5d   %s\n", i, h->freqs[i], h->stats[i], h->keys[i]);
        }else{
            fprintf(stream,"%5d %5d %5d   %s\n",i, h->freqs[i], h->stats[i], "");
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
 * Prints out a line of data from the hash table to reflect the state
 * the table was in when it was a certain percentage full.
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
