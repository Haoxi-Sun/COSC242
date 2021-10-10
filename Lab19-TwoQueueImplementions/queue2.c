#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "mylib.h"

typedef struct q_item *q_item;

struct q_item{
    double item;
    q_item next;
};

struct queue{
    q_item first;
    q_item last;
    int length;
};

queue queue_new(){
    queue q = emalloc(sizeof *q);
    q->first = NULL;
    q->last = NULL;
    q->length = 0;
    return q;
}

void enqueue(queue q, double item){
    q_item new_item = emalloc(sizeof *new_item);
    new_item->item = item;
    new_item->next = NULL;
    q->length++;
    if(q->first == NULL){
        q->first = new_item;
        q->last = new_item;
    }else{
        q->last->next = new_item;
        q->last = new_item;
    }
}

double dequeue (queue q){
    double item = q->first->item;
    q_item temp = q->first;
    
    if(q->length>0){
        if(q->length == 1){
            q->first = NULL;
            q->last = NULL;
        }else{
            q->first = q->first->next;
        }
        free(temp);
    }
    q->length--;
    return item;
}

void queue_print(queue q){
    q_item temp = q->first;
    while(temp != NULL){
        printf("%.2f\n",temp->item);
        temp = temp->next;
    }
}

int queue_size(queue q){
    if(q->length != 0){
        return q->length;
    }else{
        return 0;
    }
}

queue queue_free(queue q){
    q_item temp = q->first;
    while(temp != NULL){
        q_item o = temp;
        temp = temp->next;
        free(o);
    }
    free(q);
    return q;
}
