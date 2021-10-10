#include<stdio.h>
#include<stdlib.h>

int main(void){
    int n;
    int winner = 0;
    double a, b, c, score;
    double max = 0.0;

    while(4 == scanf("%d%lg%lg%lg", &n,&a,&b,&c)){
        
        if(a < b && a <c){
            score = (b+c)/2;
        }
        else if(b < a && b <c){
            score = (a+c)/2;
        }else{
            score = (a+b)/2;
        }

        if(score > max){
            max = score;
            winner = n;
        }
    }
    printf("The winner is %d, the score is %.1f.\n",winner,max);
    return EXIT_SUCCESS;
}
