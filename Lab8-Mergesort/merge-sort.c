#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ARRAY_MAX 5

void merge(int *array, int *workspace, int len){
    int i, j, v, m;
    m = len/2;
    v = 0;
    i = 0;
    j = m;

    while(i<m && j<len){
        if(array[i]<array[j]){
            workspace[v] = array[i];
            i++;
            v++;
        }
        else if(array[j]<array[i]){
            workspace[v] = array[j];
            j++;
            v++;
        }
    }
    while(i<m){
        workspace[v] = array[i];
        v++;
        i++;
    }
    while(j<len){
        workspace[v] = array[j];
        v++;
        j++;
    }
}

void merge_sort(int *a,int *w, int n){
    int i;
    
    if(n<2) return;
    
    merge_sort(a,w,(n/2));
    merge_sort((a+(n/2)),w,(n-(n/2)));

    merge(a,w,n);

    for(i=0;i<n;i++){
        a[i] = w[i];
    }
}

int main(void){
    int my_array[ARRAY_MAX];
    int temp[ARRAY_MAX];
    clock_t start, end;
    int i, count = 0;

    while(count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])){
        count++;
    }
    start = clock();
    merge_sort(my_array, temp,count);
    end = clock();
    
    for(i=0; i<count; i++){
        printf("%d\n", temp[i]);
    }
    fprintf(stderr, "%d %f\n", count, (end-start)/(double)CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}
