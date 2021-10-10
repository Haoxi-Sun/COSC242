#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "flexible.h"

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
void quicksort(int *a, int length){
    int pivot, i, j,temp,q,w,r;

    if(length < 2) return;

    pivot = a[0];
    i = -1;
    j = length;

    while(1){
        do{
            i++;
            printf("i a[i]: %d %d\n",i, a[i]);
        }while(a[i] < pivot);
        do{
            j--;
            printf("j a[j]: %d %d\n",j, a[j]);
        }while(a[j] > pivot);
        printf("pivot: %d\n",pivot);
        if(i<j){
            printf("do if\n");
            temp = a[j];
            a[j] = a[i];
            a[i] = temp;
            for( r = 0; r<length; r++){
                printf("ALL:  %d\n",a[r]);
            }
        }else{
            break;
        }
    }
    quicksort(a, j+1);
    printf("j+1: %d\n", j+1);
    for( q = 0; q<(j+1); q++){
            printf("left:  %d\n",a[q]);
    }
    quicksort(a+(j+1), length-j-1);
    printf("length-j-1: %d\n", length-j-1);
    for( w = 0; w<(j+1); w++){
                printf("right:  %d\n",(a+(j+1))[w]);
    }
}

void flexarray_sort(flexarray f) {
    quicksort(f->items,f->itemcount);
}

void flexarray_free(flexarray f) {
    /* free the memory associated with the flexarray */
    free(f->items);
}

