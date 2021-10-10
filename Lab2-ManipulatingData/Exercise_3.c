#include<stdio.h>
#include <stdlib.h>
#include<math.h>

double sq(double num) {
    return num * num;
}

int main(void){
    double j1[5],j2[5],j3[5],a,b,c,mean1,mean2,mean3;
    double sum1 = 0;
    double sum2 = 0;
    double sum3 = 0;
    double ds1 = 0;
    double ds2 = 0;
    double ds3 = 0;
 
    int n,index,num;
    int i = 0;


    int regur[5];
    
    while(4 == scanf("%d%lg%lg%lg",&n, &a,&b,&c)){
        j1[i] = a;
        j2[i] = b;
        j3[i] = c;

        regur[i] = n;
        i++;
        printf("%d %f\n",regur[i],j1[i]);
        }

    /* calculate each mean. */
    for(index = 0; index < 5; index++){
        sum1 += j1[index];
        sum2 += j2[index];
        sum3 += j3[index];
    }
    mean1 = sum1/5;
    mean2 = sum2/5;
    mean3 = sum3/5;

    /* calculate each srandard deviation. */
    for(num = 0; num < 5; num++){
        ds1 += sq(fabs(j1[num] - mean1));
        ds2 += sq(fabs(j2[num] - mean2));
        ds3 += sq(fabs(j3[num] - mean3));
    }
    
    printf("          Average SD\n");
    printf("judge 1 : %.1f%7.1f\n",mean1, sqrt(ds1/4));
    printf("judge 2 : %.1f%7.1f\n",mean2, sqrt(ds2/4));
    printf("judge 3 : %.1f%7.1f\n",mean3, sqrt(ds3/4));
  
    return EXIT_SUCCESS;
}
