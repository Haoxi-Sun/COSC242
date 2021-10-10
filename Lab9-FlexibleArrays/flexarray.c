#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "flexible.h"
#define MAX 10000

struct flexarrayrec {
    int capacity;
    int itemcount;
    int *items;
};

flexarray flexarray_new() {
    flexarray result = emalloc(sizeof *result);
    result->capacity = 2;
    result->itemcount = 0;
    result->items = emalloc(result->capacity * sizeof result->items[0]);
    return result;
}

void flexarray_append(flexarray f, int num) {
    if (f->itemcount == f->capacity) {
        /* do the old "double the capacity" trick */
        f->capacity += f->capacity;
        f->items = erealloc(f->items, f->capacity * sizeof f->items[0]);
    }
    /* insert the item in the last free space */
    f->items[f->itemcount++] = num;
}

void flexarray_print(flexarray f) {
    /* a "for" loop to print out each cell of f->items */
    int i;
    for(i=0; i<f->itemcount;i++){
        printf("%d\n",f->items[i]);
    }
}

void merge(int *array, int *workspace, int len){
    int i, j, v, m;
    i = 0;
    m = len/2;
    j = m;
    v = 0;

    while(i<m && j<len){
        if(array[i]<array[j]){
            workspace[v] = array[i];
            v++;
            i++;
        }
        else if(array[j]<array[i]){
            workspace[v] = array[j];
            v++;
            j++;
        }
    }
    while(i<m){
        workspace[v] = array[i];
        i++;
        v++;
    }
    while(j<len){
        workspace[v] = array[j];
        j++;
        v++;
    }
}

void merge_sort(int *a, int *w, int n){
    int i;
    if(n<2) return;

    merge_sort(a,w,n/2);
    merge_sort(a+(n/2),w,n-(n/2));

    merge(a,w,n);

    for(i=0; i<n;i++){
        a[i]=w[i];
    }
}

void flexarray_sort(flexarray f) {
    int num = f->itemcount;
    int temp[MAX];
    merge_sort(f->items,temp, num);
}

void flexarray_free(flexarray f) {
    /* free the memory associated with the flexarray */
    free(f->items);
}
