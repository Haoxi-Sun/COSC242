#include<stdio.h>
#include<stdlib.h>

int is_prime(int num){
    int i;
    for(i=2;i<num;i++){
        if(num % i==0) return 0;
    }
    return 1;
}

int main(void){
    int num = 2;
    int num_printed = 0;
    while(num_printed<200){
        if(is_prime(num)){
            printf("%5d",num);
            num_printed++;

            if(num_printed%10 == 0) printf("\n");
        }
        num++;
    }
    return EXIT_SUCCESS;
}
