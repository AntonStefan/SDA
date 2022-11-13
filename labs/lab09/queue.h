#ifndef QUEUE
#define QUEUE
    #include <stdio.h>
    #include <stdlib.h>
    #include "node.h"

    typedef struct Queue{
        node *head, *tail;
        int len;
    }Queue;

    void init_queue(Queue **q);
    void free_queue(Queue **q);
    int add_queue(Queue *q, int val1, int val2);
    void pop_queue(Queue *q);
    void print_queue(Queue *q);
    int is_empty_queue(Queue *q);
    
#endif