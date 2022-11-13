#include "queue.h"

void init_queue(Queue **q){
    *q = (Queue*)malloc(sizeof(Queue));
    (*q)->head = NULL;
    (*q)->tail = NULL;
    (*q)->len = 0;
}

void free_queue_sll(node *current){
    if(current == NULL)
        return;
    free_queue_sll(current->next);
    free(current);
}

void free_queue(Queue **q){
    free_queue_sll((*q)->head);
    free(*q);
    *q = NULL;
}

int add_queue(Queue *q, int val){
    node *new = (node*)malloc(sizeof(node));
    if(new == NULL)
        return 0;
    new->data = val;
    new->next = NULL;
    if(q->len == 0){
        q->head = new;
        q->tail = new;
        (q->len)++;
        return 1;
    }
    q->tail->next = new;
    q->tail = new;
    (q->len)++;
    return 1;
}

int pop_queue(Queue *q){
    if(q->len == 0)
        return 0;
    node *aux = q->head;
    int val = aux->data;
    q->head = q->head->next;
    free(aux);
    (q->len)--;
    return val;
}

void print_queue(Queue *q){
    node *i;
    for(i = q->head; i != NULL; i = i->next)
        printf("%d ", i->data);
    printf("\n");
}

int is_empty_queue(Queue *q){
    if(q->len == 0)
        return 1;
    return 0;
}