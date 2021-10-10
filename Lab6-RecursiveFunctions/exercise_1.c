#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ARRAY_MAX 5
#define LEN 80

void print_array(char *a[], int n){
    if(n>0){
        printf("%s\n",a[0]);
        print_array(a+1, n-1);
    }
}
void sort(char *s[], int n){
    char *temp;
    int p, j;

    for(p = 1; p < n; p++){
        temp = s[p];
        /*move each item that is to the lelf of position p
          and is greater than key*/
        for(j = p-1; j >= 0; j--){
            if(strcmp(s[j], temp) > 0){
                s[j+1] = s[j];
            }else{
                break;
            }
        }
        /*put key in the leftmost vacated position*/
        s[j+1] = temp;
    }
}

int main(void){
    char word[LEN];
    char *my_array[ARRAY_MAX];
    int num_words;
    int i;

    num_words = 0;
    while(num_words < ARRAY_MAX && 1 == scanf("%79s", word)){
        my_array[num_words] = malloc((strlen(word)+1)*sizeof my_array[0][0]);
        strcpy(my_array[num_words], word);
        num_words++;
    }

    sort(my_array, num_words);

    print_array(my_array, num_words);
    
    for(i=0; i<num_words; i++){
        free(my_array[i]);
    }

    return EXIT_SUCCESS;
}
