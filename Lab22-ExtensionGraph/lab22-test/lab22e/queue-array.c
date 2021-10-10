#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "mylib.h"

struct queue{
    int capacity;
    int num_items;
    int head;
    int *items;
};

queue queue_new(){
    int i;
    int default_size = 7;
    queue q = emalloc(sizeof *q);
    q->capacity = default_size;
    q->num_items = 0;
    q->head = 0;
    q->items = emalloc(q->capacity * sizeof q->items[0]);
    for(i=0;i<q->capacity;i++){
        q->items[i] = 0;
    }
    return q;
}

void enqueue(queue q, double item){
    if(q->num_items < q->capacity){
        q->items[(q->head+q->num_items++) % q->capacity] = item;
    }
}

double dequeue(queue q){
    int temp = q->head;
    if(q->num_items>0){
        q->head = (q->head+1) % q->capacity;
        q->num_items--;
        return q->items[temp];
    }
    return 0;
}

void queue_print(queue q){
    int i;
    for(i=0;i<q->num_items;i++){
        if(q->items[(i+q->head) % q->capacity] != 0){
            printf("%d\n",q->items[(i+q->head) % q->capacity]);
        }
    }
}

void queue_print_info(queue q){
    int i;
    printf("capacity %d, num_items %d, head %d\n[", q->capacity,q->num_items,
           q->head);
    for(i=0;i<q->capacity;i++){
        printf("%s%2d", i==0 ? "":", ", q->items[i]);
    }
    printf("]\n");
}

int queue_size(queue q){
    return q->num_items;
}

queue queue_free(queue q){
    free(q->items);
    free(q);
    return q;
}
