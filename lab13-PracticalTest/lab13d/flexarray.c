#include<stdio.h>
#include<stdlib.h>
#include"flexarray.h"

struct flexarrayrec{
    int capacity;
    int itemcount;
    int *items;
};

void *emalloc(size_t s){
    void *result = malloc(s);
    if(NULL==result){
        fprintf(stderr,"Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

void *erealloc(void *p, size_t s){
    void *result = realloc(p,s);
    if(NULL==result){
        fprintf(stderr,"Memory reallocation failed.\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

flexarray flexarray_new(){
    flexarray result = emalloc(sizeof *result);
    result->capacity = 2;
    result->itemcount = 0;
    result->items = emalloc(result->capacity *sizeof result->items[0]);

    return result;
}

void flexarray_append(flexarray f,int num){
    if(f->itemcount == f->capacity){
        f->capacity += f->capacity;
        f->items = erealloc(f->items, f->capacity * sizeof f->items[0]);
    }
    f->items[f->itemcount++] = num;
}

void flexarray_print(flexarray f){
    int i;
    for(i=0; i<f->itemcount;i++){
       fprintf(stdout,"%d\n",f->items[i]);
    }
}

void flexarray_sort(flexarray f){
    int i, j, temp, p;
    for(p=1;p<f->itemcount;p++){
        temp = f->items[p];
        for(j=p-1;j>=0;j--){
            if(f->items[j]>temp){
                f->items[j+1] = f->items[j];
            }else{
                break;
            }
        }
        f->items[j+1] = temp;
        if(p==f->itemcount/2-1){
            for(i=0;i<f->itemcount;i++){
                fprintf(stderr,"%d\n",f->items[i]);
            }
        }
    }
}

void flexarray_free(flexarray f){
    free(f->items);
    free(f);
}


