/**
 * @file mylib.c
 * functions for COSC242 Assignment.
 * 
 * Author: Elsie Sun, Grace Jan, Xiaoqian Yan.
 */
#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include <assert.h>
#include <ctype.h>


/**
 * Error checking version of malloc:
 * attempt to allocate memory using malloc and
 * return the memory address (pointer) as success 
 *
 * Print an error message on stderr and then terminate the program as failure
 * because it cannot allocate the memory that we want .
 *
 * @param s - the size of the type or variable. 
 * @return result - the memory address of the varaible/type
 */
void *emalloc(size_t s){
    void *result = malloc(s);
    if(NULL==result){
        fprintf(stderr,"memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

/**
 * Error checking version of realloc:
 * attempt to reallocate memory using realloc and
 * return the memory address (pointer) as success
 *
 * Print an error message on stderr and then terminate the program as failure
 * because it cannot allocate the memory that we want .
 *
 *@param *p - pointer to the first memory has allocated using malloc 
 * @param s - the size of the type or variable.
 * @return result - the memory address of the new varaible/type
 */
void *erealloc(void *p, size_t s){
    void *result = realloc(p, s);
    if(NULL==result){
        fprintf(stderr,"memory reallocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}


/**
 *Function for getting words
 *
 *@param *s - words to get
 *@param limit - the maximum length
 *@param stream - a stream to get the words from.
 */
int getword(char *s, int limit, FILE *stream){
    int c;
    char *w = s;
    assert(limit > 0 && s != NULL && stream != NULL);

    /* skip to the start of the word */
    while(!isalnum(c = getc(stream)) && EOF != c)
        ;
    if (EOF == c) {
        return EOF;
        /* reduce limit by 1 to allow for the \0 */ 
    } else if (--limit > 0){
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
