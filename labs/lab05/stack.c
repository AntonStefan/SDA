#include "stack.h"

void init_stack(Stack **s){
    *s = (Stack*)malloc(sizeof(Stack));
    (*s)->top = NULL;
    (*s)->len = 0;
}

void free_stack_sll(node *current){
    if(current == NULL)
        return;
    free_stack_sll(current->next);
    free(current);
}

void free_stack(Stack **s){
    free_stack_sll((*s)->top);
    free(*s);
    *s = NULL;
}

int add_stack(Stack *s, int val){
    node *new = (node*)malloc(sizeof(node));
    if(new == NULL)
        return 0;
    new->data = val;
    new->next = s->top;
    s->top = new;
    (s->len)++;
    return 1;
}

int pop_stack(Stack *s){
    if(s->len == 0)
        return 0;
    node *aux = s->top;
    int val = aux->data;
    s->top = s->top->next;
    free(aux);
    (s->len)--;
    return val;
}

void print_stack(Stack *s){
    node *i;
    for(i = s->top; i != NULL; i = i->next)
        printf("%d ", i->data);
    printf("\n");
}

int is_empty_stack(Stack *s){
    if(s->len == 0)
        return 1;
    return 0;
}
