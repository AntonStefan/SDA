#ifndef WGRAPH
#define WGRAPH

    #include "Gen_Utility.h"
    #include "Generic_Heap.h"

    #define INF 1000000

    typedef struct Node{
        int val;
        int weight;
        struct Node* next;
    }Node;
    typedef struct WGraph{
        int nr_nodes;
        struct Node** neighbours;
    }WGraph;
    typedef struct DijNode{
        int node;
        int weight;
    }DijNode;
    typedef struct Link{
        int node1;
        int node2;
        int weight;
    }Link;

    void WGRAPH_init(WGraph **myGraph, int nr_nodes);
    int WGRAPH_add_link(WGraph *myGraph, int src, int dest, int weight);
    void WGRAPH_print_links(WGraph *myGraph);
    void WGRAPH_Prim(WGraph *myGraph);
    void WGRAPH_Kruskal(WGraph *myGraph);
    int *WGRAPH_topsort(WGraph *myGraph);
    WGraph *WGRAPH_transpose(WGraph *myGraph);
    void WGRAPH_free(WGraph **myGraph);

#endif