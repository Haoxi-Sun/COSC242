#include<stdio.h>
#include<stdlib.h>

int is_prime(int candidate){
    int n;
    for(n=2; n<candidate; n++){
        if(candidate%n == 0){
            return 0;
        }
        return 1;
    }
    return 0;
}

int main(void){
    int num = 2;
    int num_printed = 0;

    while(num_printed <= 100){
        if(is_prime(num)==1){
            printf("%d ",num);
            num_printed++;
         }
         if(num_printed%5 == 0){
                printf("\n");
         }

        num++;
    }
    return 0;
}
