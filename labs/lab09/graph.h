#ifndef GRAPH
#define GRAPH
    
    #include <stdio.h>
    #include <stdlib.h>
    #include "queue.h"

    typedef struct Node{
        int val;
        struct Node* next;
    }Node;
    typedef struct Graph{
        int nr_nodes;
        struct Node** neighbours;
    }Graph;

    void GRAPH_init(Graph **graph, int nr_nodes);
    int GRAPH_add_link(Graph *graph, int src, int dest);
    void GRAPH_print_links(Graph *graph);
    int *GRAPH_distance(Graph *graph, int start);
    int *GRAPH_topsort(Graph *graph);
    void GRAPH_print_SCC(Graph *graph);
    void GRAPH_free(Graph **graph);



#endif