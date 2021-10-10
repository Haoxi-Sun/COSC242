#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "queue.h"

typedef struct q_item *q_item;

struct q_item{
    double item;
    q_item next;
};

struct queue{
    int length;
    q_item first;
    q_item last;
};

queue queue_new(){
    queue q = emalloc(sizeof *q);
    q->first = NULL;
    q->last = NULL;
    q->length = 0;
    return q;
}

void enqueue(queue q, double item){
    q_item i = emalloc(sizeof *i);
    i->item = item;
    i->next = NULL;
    if(q->length == 0){
        q->first = i;
    }else{
        q->last->next = i;
    }
    q->last = i;
    q->length++;
}

double dequeue(queue q){
    double rm = q->first->item;
    q_item temp = q->first;
    if(q->length > 0){
        if(q->length == 1){
            q->first = NULL;
            q->last = NULL;
        }else{
            q->first = q->first->next;
        }
        free(temp);
    }
    q->length--;
    return rm;
}

void queue_print(queue q){
    q_item temp = q->first;
    while(temp != NULL){
        printf("%.2f\n", temp->item);
        temp = temp->next;
    }
}

void queue_print_info(queue q){
    if(q->length == 0){
        printf("The queue is empty\n");
    }else{
        printf("first %.2f, last %.2f, length %d\n", q->first->item,
               q->last->item, q->length);
    }
}

int queue_size(queue q){
    if(q->length != 0){
        return q->length;
    }else{
        return 0;
    }
}

void queue_free_aux(q_item i){
    free(i);
}

queue queue_free(queue q){
    q_item temp = q->first;
    while(temp != NULL){
        q_item i = temp;
        temp = temp->next;
        free(i);
    }
    free(q);
    return q;
}
