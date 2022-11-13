#ifndef WGRAPH
#define WGRAPH

    #include "Gen_Utility.h"
    #include "Generic_Heap.h"

    typedef struct Node{
        int val;
        int weight;
        struct Node* next;
    }Node;
    typedef struct WGraph{
        int nr_nodes;
        struct Node** neighbours;
    }WGraph;
    typedef struct DijHeap{
        int node;
        int weight;
    }DijHeap;


    void WGRAPH_init(WGraph **myGraph, int nr_nodes);
    int WGRAPH_add_link(WGraph *myGraph, int src, int dest, int weight);
    void WGRAPH_print_links(WGraph *myGraph);
    int **WGRAPH_Roy_Floyd(WGraph *myGraph);
    int *WGRAPH_Dijkstra(WGraph *myGraph, int src);
    int *WGRAPH_Bellman_Ford(WGraph *myGraph, int src);
    int **WGRAPH_Johnson(WGraph *myGraph);
    void WGRAPH_free(WGraph **myGraph);

#endif