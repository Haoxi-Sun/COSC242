#include<stdio.h>
#include<stdlib.h>

#define ARRAY_SIZE 10000

void sort(int s[], int n){
    int p, j,temp;

    for(p = 1; p < n; p++){
        temp = s[p];
        /*move each item that is to the lelf of position p
          and is greater than key*/
        for(j = p-1; j >= 0; j--){
            if(s[j]>temp){
                s[j+1] = s[j];
            }else{
                break;
            }
        }
        /*put key in the leftmost vacated position*/
        s[j+1] = temp;
    }
}

int binary_search(int s[],int l, int r, int num){
    if(r>=l){
        int mid = l+(r-l)/2;

        if(s[mid]==num){
            return mid;
        }
        if(s[mid]>num){
            return binary_search(s,l,mid-1,num);
        }
        if(s[mid]<num){
            return binary_search(s,mid+1,r,num);
        }
    }
    return -1;
}

int main(void){

    FILE *file1 = fopen("data.txt","r");
    FILE *file2 = fopen("query.txt","r");
    int file1_array[ARRAY_SIZE];
    int file2_array[ARRAY_SIZE];
    int f1_words, f2_words;
    int i;

    if(file1 == NULL || file2 == NULL){
        fprintf(stderr, " can`t find file.\n");
        return EXIT_FAILURE;
    }

    /* file1 */
    f1_words = 0;
    while(f1_words<ARRAY_SIZE && 1==fscanf(file1,"%d",&file1_array[f1_words])){
        f1_words++;
    }
    /* file2 */
    f2_words = 0;
    while(f2_words<ARRAY_SIZE && 1==fscanf(file2,"%d",&file2_array[f2_words])){
        f2_words++;
    }
    
    fclose(file1);
    fclose(file2);
    
    sort(file1_array, f1_words);
    

    for(i=0; i<f2_words; i++){
        if(binary_search(file1_array,0,f1_words-1,file2_array[i]) != -1){
            printf("+\n");
        }else{
            printf("-\n");
        }
    }

    return EXIT_SUCCESS;
}
