#include<stdio.h>
#include<stdlib.h>

int main(void){
    int a;
    int winner = 0;
    double s1,s2,s3,score;
    double max = 0.0;

    while(4==scanf("%d%lg%lg%lg",&a,&s1,&s2,&s3)){
        if(s1<s2 &&s1<s3){
            score = (s2+s3)/2;
        }else if(s2<s1 && s2<s3){
            score = (s1+s3)/2;
        }else{
            score = (s1+s2)/2;
        }

        if(score > max){
            max = score;
            winner = a;
        }
    }

    fprintf(stdout,"%d\n",winner);
    return EXIT_SUCCESS;
}
