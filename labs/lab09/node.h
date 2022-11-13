#ifndef NODE
#define NODE

    typedef struct Data{
        int val1;
        int val2;
    }Data;

    typedef struct node{
        Data data;
        struct node *next;
    }node;
    
#endif