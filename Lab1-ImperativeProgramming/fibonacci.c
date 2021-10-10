#include<stdio.h>
int main(void){
    int f = 0;
    int g = 1;
    int i, temp;

    for(i = 1; i<=40; i++){
        printf("%d ",g);
        temp = g;
        g = g + f;
        f = temp;

        if(i%5==0){
            printf("\n");
        }
    }
    
    return 0;
}
