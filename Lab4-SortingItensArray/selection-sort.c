#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ARRAY_MAX 30000

void selection_sort(int *a, int n){
    int p, key,j, temp;
    for(p=0; p<n-1; p++){
        key = p;
        /*find the smallest element from p to (p+1) which called j.*/
        for(j=p+1; j<n; j++){
            if(a[key] > a[j]){
                key = j;
            }
        }
        /*swap the item to position p.*/
        temp = a[p];
        a[p] = a[key];
        a[key] = temp;
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
    selection_sort(my_array, count);
    end = clock();

    for(i=0; i<count; i++){
        printf("%d\n", my_array[i]);
    }
    fprintf(stderr,"%d %f\n", count, (end-start)/(double)CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}
