#include "WGraph.h"

// Initialize cost graph
void WGRAPH_init(WGraph **myGraph, int nr_nodes){
    *myGraph = (WGraph*)malloc(sizeof(WGraph));
    (*myGraph)->nr_nodes = nr_nodes;
    (*myGraph)->neighbours = (Node**)malloc((nr_nodes) * sizeof(Node*));
    int i;
    for(i = 0; i < nr_nodes; i++)
        (*myGraph)->neighbours[i] = NULL;
}
// Add link to the cost graph
int WGRAPH_add_link(WGraph *myGraph, int src, int dest, int weight){
    if(myGraph->neighbours[src] == NULL){
        myGraph->neighbours[src] = (Node*)malloc(sizeof(Node));
        if(myGraph->neighbours[src] == NULL)
            return -1;
        myGraph->neighbours[src]->val = dest;
        myGraph->neighbours[src]->weight = weight;
        myGraph->neighbours[src]->next = NULL;
        return 0;
    }
    Node *aux = myGraph->neighbours[src];
    while(aux->next != NULL){
        aux = aux->next;
    }
    aux->next = (Node*)malloc(sizeof(Node));
    if(aux->next == NULL)
        return -1;
    aux->next->val = dest;
    aux->next->weight = weight;
    aux->next->next = NULL;
    return 0;
}
// Print all links in the graph
void WGRAPH_print_links(WGraph *myGraph){
    Node *aux;
    int i;
    for(i = 0; i < myGraph->nr_nodes; i++){
        printf("%d-> ", i);
        aux = myGraph->neighbours[i];
        while(aux != NULL){
            printf("%d weight: %d\n    ", aux->val, aux->weight);
            aux = aux->next;
        }
        printf("\n");
    }
}
// Compare function for Min Heap with DijNode 
int cmpDij(void *x, void *y){
    return ((DijNode*)y)->weight - ((DijNode*)x)->weight;
}
// Print minimum spanning tree
void WGRAPH_Prim(WGraph *myGraph){
    Heap *myHeap;
    DijNode cItem, nItem;
    Node *aux;
    int src;
    int t_cost;
    int nr_nodes;
    int *dist;
    int *father;
    int *vis;
    int i;
    nr_nodes = myGraph->nr_nodes;
    //Initialize source(start node)
    src = 0;
    // Initialize visited array
    vis = (int*)calloc(nr_nodes, sizeof(int));
    // Initialize distance array
    dist = (int*)malloc((nr_nodes) * sizeof(int));
    for(i = 0; i < nr_nodes; i++)
        dist[i] = INF;
    dist[src] = 0;
    // Initialize father array
    father = (int*)malloc(nr_nodes * sizeof(int));
    for(i = 0; i < nr_nodes; i++)
        father[i] = i;
    // Initialize heap
    HEAP_init(&myHeap, sizeof(DijNode));
    // Prim's algorithm
    cItem.node = src;
    cItem.weight = dist[src];
    HEAP_insert(myHeap, &cItem, cmpDij);
    while(myHeap->vect->len != 0){
        cItem = *((DijNode*)myHeap->vect->arr);
        HEAP_remove_root(myHeap, cmpDij);
        vis[cItem.node] = 1;
        aux = myGraph->neighbours[cItem.node];
        while(aux != NULL){
            if(vis[aux->val] == 0){
                if(dist[aux->val] > aux->weight){
                    dist[aux->val] =  aux->weight;
                    father[aux->val] = cItem.node;
                }
                // Add nex tnode to the heap
                nItem.node = aux->val;
                nItem.weight = aux->weight;
                HEAP_insert(myHeap, &nItem, cmpDij);
            }
            aux = aux->next;
        }
    }
    // Calculate total cost
    t_cost = 0;
    for(i = 0; i < nr_nodes; i++)
        t_cost += dist[i];
    // Print links
    printf("MST Links:\n");
    for(i = 1; i < nr_nodes; i++)
        printf("%d %d\n", i, father[i]);
    // Print total cost
    printf("MST Total Cost: %d\n", t_cost);

    // Free memory
    HEAP_free(&myHeap);
    free(father);
    free(dist);
    free(vis);
}
// Compare function for Min Heap with Link 
int cmpLink(void *x, void *y){
    return ((Link*)y)->weight - ((Link*)x)->weight;
}
// Print minimum spanning tree
void WGRAPH_Kruskal(WGraph *myGraph){
    Heap *myHeap;
    Link link;
    Node *aux;
    int c1, c2;
    int t_cost;
    int nr_nodes;
    int *conex;
    int i;

    t_cost = 0;
    nr_nodes = myGraph->nr_nodes;
    // Initialize conex array
    conex = (int*)malloc(nr_nodes * sizeof(int));
    for(i = 0; i < nr_nodes; i++)
        conex[i] = i;
    // Initialize heap
    HEAP_init(&myHeap, sizeof(Link));
    // Add links to min heap
    for(i = 0; i < myGraph->nr_nodes; i++){
        aux = myGraph->neighbours[i];
        while(aux != NULL){
            if(aux->val > i){
                link.node1 = i;
                link.node2 = aux->val;
                link.weight = aux->weight;
                HEAP_insert(myHeap, &link, cmpLink);
            }
            aux = aux->next;
        }
    }
    // Kruskal's algorithm
    printf("MST Links:\n");
    while(myHeap->vect->len != 0){
        link = *((Link*)myHeap->vect->arr);
        if(conex[link.node1] != conex[link.node2]){
            printf("%d %d\n", link.node1, link.node2);
            t_cost += link.weight;
            c1 = conex[link.node1];
            c2 = conex[link.node2];
            for(i = 0; i < nr_nodes; i++)
                if(conex[i] == c2)
                    conex[i] = c1;
        }
        HEAP_remove_root(myHeap, cmpLink);
    }
    printf("MST Total Cost: %d\n", t_cost);

    // Free memory
    HEAP_free(&myHeap);
    free(conex);
}
// Generate topological order array
void DFS_topsort(WGraph *graph, int cNode, int *visited, int *topsort, int *k){
    if(visited[cNode] == 1)
        return;
    visited[cNode] = 1;
    Node *aux = graph->neighbours[cNode];
    while(aux != NULL){
       DFS_topsort(graph, aux->val, visited, topsort, k);
       aux = aux->next;
    }
    topsort[*k] = cNode;
    (*k)--;
}
// Return array with topological order of graph
int *WGRAPH_topsort(WGraph *myGraph){
    int *topsort;
    int *visited;
    int i;
    int k;
    topsort = (int*)malloc(myGraph->nr_nodes * sizeof(int));
    visited = (int*)calloc(myGraph->nr_nodes, sizeof(int));
    k = myGraph->nr_nodes - 1;
    for(i = 0; i < myGraph->nr_nodes; i++)
        if(visited[i] == 0)
            DFS_topsort(myGraph, i, visited, topsort, &k);

    free(visited);
    return topsort;
}
// Return transpose graph
WGraph *WGRAPH_transpose(WGraph *myGraph){
    WGraph *tGraph;
    Node *aux;
    int i;
    WGRAPH_init(&tGraph, myGraph->nr_nodes);
    tGraph->nr_nodes = myGraph->nr_nodes;
    for(i = 0; i < myGraph->nr_nodes; i++){
        aux = myGraph->neighbours[i];
        while(aux != NULL){
            WGRAPH_add_link(tGraph, aux->val, i, aux->weight);
            aux = aux->next;
        }
    }
    return tGraph;
}
// free node list
void free_list(Node *root){
    if(root == NULL)
        return;
    free_list(root->next);
    free(root);
}
// Free cost graph memory
void WGRAPH_free(WGraph **myGraph){
    int nr_nodes;
    int i;
    nr_nodes = (*myGraph)->nr_nodes;
    for(i = 0; i < nr_nodes; i++)
        free_list((*myGraph)->neighbours[i]);
    free((*myGraph)->neighbours);
    free(*myGraph);
    *myGraph = NULL;
}