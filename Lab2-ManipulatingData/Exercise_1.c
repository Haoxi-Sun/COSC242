#include<stdio.h>
#include<stdlib.h>

int main(void){
    double s1, s2, s3;
    printf("Input three scores from 0.0 to 6.0: ");
    fflush(stdout);

    scanf("%lg %lg %lg",&s1, &s2, &s3);

    if(s1 <= (6.0/3)){
        printf("The outcome is %2.1f\n", (s2+s3)/2);
    }
    else if(s2 < (6.0/3)){
        printf("The outcome is %2.1f\n", (s1+s3)/2);
    }else{
        printf("The outcome is %2.1f\n", (s1+s2)/2);
    }
    return EXIT_SUCCESS;
}
