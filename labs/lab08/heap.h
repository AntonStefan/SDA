#ifndef HEAP
#define HEAP
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>

    typedef struct node {
        int val;
        struct node *left, *right;
    } node;    
    typedef struct Heap {
        int no_nodes;
        struct node *root;
    } Heap;

    void HEAP_init(Heap **heap);
    void HEAP_insert(Heap *heap, int val);
    void HEAP_heapify(Heap *heap);
    void HEAP_remove_root(Heap *heap);
    void HEAP_print_inorder(node *root);
    void HEAP_free(Heap **heap);

#endif