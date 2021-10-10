#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "mylib.h"

int main(void){
     
    queue q = queue_new();
    enqueue(q, 1.2);
    enqueue(q, 2.3);
    enqueue(q, 3.4);
    enqueue(q, 4.5);
    enqueue(q, 5.6);
    
    queue_print(q);

    printf("Dequeue: %.2f\n",dequeue(q));
    queue_print(q);
    printf("Size : %d\n", queue_size(q));
    queue_free(q);
    return 0;
}
