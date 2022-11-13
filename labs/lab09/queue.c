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

int add_queue(Queue *q, int val1, int val2){
    node *new = (node*)malloc(sizeof(node));
    if(new == NULL)
        return 0;
    new->data.val1 = val1;
    new->data.val2 = val2;
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

void pop_queue(Queue *q){
    if(q->len == 0)
        return;
    node *aux = q->head;
    q->head = q->head->next;
    free(aux);
    (q->len)--;
}

void print_queue(Queue *q){
    node *i;
    for(i = q->head; i != NULL; i = i->next)
        printf("%d %d | ", i->data.val1, i->data.val2);
    printf("\n");
}

int is_empty_queue(Queue *q){
    if(q->len == 0)
        return 1;
    return 0;
}