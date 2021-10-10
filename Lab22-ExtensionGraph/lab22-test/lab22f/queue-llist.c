#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "queue.h"

typedef struct q_item *q_item;

struct q_item{
    int item;
    q_item next;
};

struct queue{
    int length;
    q_item first;
    q_item last;
};

queue queue_new(){
    queue q = emalloc(sizeof *q);
    q->length = 0;
    q->first = NULL;
    q->last = NULL;
    return q;
}

void enqueue(queue q, int item){
    q_item i = emalloc(sizeof *i);
    i->item = item;
    i->next = NULL;

    if(q->length == 0){
        q->first = i;
    }else{
        q->first->next = i;
    }
    q->last = i;
    q->length++;
}

int dequeue(queue q){
    int i = q->first->item;
    q_item temp = q->first;

    if(q->length >0){
        if(q->length==1){
            q->first = NULL;
            q->last =NULL;
        }else{
            q->first = q->first->next;
        }
        free(temp);
    }
    q->length--;
    return i;
}

void queue_print(queue q){
    q_item temp = q->first;
    while(temp != NULL){
        printf("%d\n",temp->item);
        temp = temp->next;
    }
}

void queue_print_info(queue q){
    if(q->length == 0){
        printf("The queue is empty\n");
    }else{
        printf("first %d, last %d, length %d\n",q->first->item,
               q->last->item, q->length);
    }
}

int queue_size(queue q){
    if(q->length == 0) return 0;
    return q->length;
}

void queue_free_aux(q_item i){
    free(i);
}

queue queue_free(queue q){
    q_item i = q->first;
    while(i!=NULL){
        q_item temp = i;
        temp = temp->next;
        free(i);
    }
    free(q);
    return q;
}
