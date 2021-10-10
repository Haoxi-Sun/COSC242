#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>

#define ARRAY_SIZE 5

int check_repeats(int *a, int num){
    int i;
    int count = 0;
    for(i=0; i<ARRAY_SIZE; i++){
        if(a[i] == num){
            count++;
        }
    }
    return count;
}

int is_contain_num(int *contains, int num){
    int i;
    for(i=0; i<ARRAY_SIZE; i++){
        if(contains[i] == num){
            return 1;
        }
    }
    return 0;
}

void initialise(int *a){
    int i;
    for(i=0; i<ARRAY_SIZE; i++){
        a[i] = -1;
    }
}

void display_repeats(int *a){
    int i;
    int contain[ARRAY_SIZE];
    int contains_index = 0;
    int count = 0;
    
    initialise(contain);
    for(i=0; i<ARRAY_SIZE; i++){
        if(is_contain_num(contain,a[i])==0){
            count = check_repeats(a,a[i]);
            contain[contains_index] = a[i];
            contains_index++;

            if(count>1){
                printf("%d repeats %d time.\n",a[i], count);
            }
        }
    }
}
int main(void){
    int *my_dynamic_array;
    int i = 0;

    my_dynamic_array = malloc(ARRAY_SIZE * sizeof my_dynamic_array[0]);
    if(NULL == my_dynamic_array){
        fprintf(stderr, "memoery allocation failed!\n");
        return EXIT_FAILURE;
    }

    for(i = 0; i < ARRAY_SIZE; i++){
        my_dynamic_array[i] = rand() % ARRAY_SIZE;
    }

    printf("What`s in the array:\n");
    for(i = 0; i < ARRAY_SIZE; i++){
        printf("%d ", my_dynamic_array[i]);
    }
    printf("\n");

    display_repeats(my_dynamic_array);

    free(my_dynamic_array);
    return EXIT_SUCCESS;
}
