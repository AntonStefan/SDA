#ifndef STACK
#define STACK
    #include <stdio.h>
    #include <stdlib.h>
    #include "node.h"

    typedef struct Stack{
        node *top;
        int len;
    }Stack;

    void init_stack(Stack **s);
    void free_stack(Stack **s);
    int add_stack(Stack *s, int val);
    int pop_stack(Stack *s);
    void print_stack(Stack *s);
    int is_empty_stack(Stack *s);

#endif