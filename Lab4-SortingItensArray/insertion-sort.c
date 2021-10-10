#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ARRAY_MAX 30000

void insertion_sort(int *a, int n){
    int p, key,j;

    for(p = 1; p < n; p++){
        key = a[p];
        /*move each item that is to the lelf of position p
          and is greater than key*/
        for(j = p-1; j >= 0; j--){
            if(a[j] > key){
                a[j+1] = a[j];
            }else{
                break;
            }
        }
        /*put key in the leftmost vacated position*/
        a[j+1] = key;
    }
}

int main(void){
    int my_array[ARRAY_MAX];
    clock_t start, end;
    int i, count = 0;

    while(count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])){
        count++;
    }
    start = clock();
    insertion_sort(my_array, count);
    end = clock();
    
    for(i=0; i<count; i++){
        printf("%d\n", my_array[i]);
    }
    fprintf(stderr, "%d %f\n", count, (end-start)/(double)CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}
