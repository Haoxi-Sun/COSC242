#include<stdio.h>
#include<stdlib.h>

void max_min(int *a, int n, int *max, int *min){
    int i;
    for(i = 0; i < n; i++){
        if(a[i] > *max){
            *max = a[i];
        }else if(a[i] < *min){
            *min = a[i];
        }
    }
}

int main(void){
    int my_array[] = {5,2,7,3,4};
    int biggest = my_array[0], smallest = my_array[0];

    max_min(my_array, 5, &biggest, &smallest);
    printf("Max value is %d, min value is %d.\n",biggest, smallest);
    return EXIT_SUCCESS;
}
