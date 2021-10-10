#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
static void array_sort(int *s, int n){
    int p, j,temp;

    for(p = 1; p < n; p++){
        temp = s[p];
        /*move each item that is to the lelf of position p
          and is greater than key*/
        for(j = p-1; j >= 0; j--){
            if(s[j]>temp){
                s[j+1] = s[j];
            }else{
                break;
            }
        }
        /*put key in the leftmost vacated position*/
        s[j+1] = temp;
    }
}

static void array_print(int *a, int n) {
    int i;
    array_sort(a,n);
    for (i = 0; i < n; i++) {
        printf("%d\n", a[i]);
    }
}
int main(void) {
    int capacity = 2;
    int itemcount = 0;
    int item;
    int *my_array = malloc(capacity * sizeof my_array[0]);
    if (NULL == my_array) {
        fprintf(stderr, "memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    while (1 == scanf("%d", &item)) {
        if (itemcount == capacity) {
            capacity += capacity;
            my_array = realloc(my_array, capacity * sizeof my_array[0]);
            if (NULL == my_array) {
                fprintf(stderr, "memory reallocation failed.\n");
                exit(EXIT_FAILURE);
            }
        }
        my_array[itemcount++] = item;
    }
    array_print(my_array, itemcount);
    free(my_array);
    return EXIT_SUCCESS;
}
