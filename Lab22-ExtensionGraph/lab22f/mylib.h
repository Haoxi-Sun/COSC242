/**
 * @file mylib.h
 * functions used for COSC242 Assignment.
 */
#ifndef MYLIB_H_
#define MYLIB_H_

#include <stdio.h>
#include <stddef.h>

extern void *emalloc(size_t);
extern void *erealloc(void *, size_t);
extern int getword(char *, int, FILE *);

#endif
