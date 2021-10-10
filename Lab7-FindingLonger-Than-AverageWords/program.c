#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define STRING_LEN 80
#define ARRAY_SIZE 100

void *emalloc(size_t s){
    void *result = malloc(s);
    if(NULL==result){
        fprintf(stderr,"Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}
void print_big_words(char *s[],int len, double average){
    if(len>0){
        if(strlen(s[0])>average){
            fprintf(stdout,"%s\n",s[0]);
        }
        print_big_words(s+1,len-1,average);
    }
}
int main(void){
    char word[STRING_LEN];
    char *wordlist[ARRAY_SIZE];
    int i, num_words;
    double average;

    num_words = 0;
    while(num_words < ARRAY_SIZE && 1==fscanf(stdin,"%79s\n",word)){
        wordlist[num_words] = emalloc((strlen(word)+1)*sizeof wordlist[0][0]);
        strcpy(wordlist[num_words], word);
        num_words++;
    }

    average = 0.0;
    for(i=0;i<num_words;i++){
        average += strlen(wordlist[i]);
    }
    if(num_words == 0){
        return EXIT_FAILURE;
    }
    average = average / num_words;
    fprintf(stderr,"%.2f\n",average);

    print_big_words(wordlist,num_words,average);

    for(i=0;i<num_words;i++){
        free(wordlist[i]);
    }
    return EXIT_SUCCESS;
}
