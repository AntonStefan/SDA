#include "WGraph.h"

// Initialize cost graph
void WGRAPH_init(WGraph **myGraph, int nr_nodes){
    *myGraph = (WGraph*)malloc(sizeof(WGraph));
    (*myGraph)->nr_nodes = nr_nodes;
    (*myGraph)->neighbours = (Node**)malloc((nr_nodes + 1) * sizeof(Node*));
    int i;
    for(i = 0; i <= nr_nodes; i++)
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
    for(i = 1; i <= myGraph->nr_nodes; i++){
        printf("%d-> ", i);
        aux = myGraph->neighbours[i];
        while(aux != NULL){
            printf("%d weight: %d\n    ", aux->val, aux->weight);
            aux = aux->next;
        }
        printf("\n");
    }
}
// Return minimum distance matrix
int **WGRAPH_Roy_Floyd(WGraph *myGraph){
    int k, i, j;
    int nr_nodes;
    int **dist;
    Node *aux;
    nr_nodes = myGraph->nr_nodes;
    // Initialize distance matrix
    dist = genMatrix_int(nr_nodes + 1, nr_nodes + 1);
    for(i = 1; i <= nr_nodes; i++)
        for(j = 1; j <= nr_nodes; j++)
            dist[i][j] = INT32_MAX / 2;
    for(i = 1; i <= nr_nodes; i++)
        dist[i][i] = 0;
    for(i = 1; i <= nr_nodes; i++){
        aux = myGraph->neighbours[i];
        while(aux != NULL){
            dist[i][aux->val] = aux->weight;
            aux = aux->next;
        }
    }
    // Roy-Floyd algorithm
    for(k = 1; k <= nr_nodes; k++)
        for(i = 1; i <= nr_nodes; i++)
            for(j = 1; j <= nr_nodes; j++)
                if(dist[i][j] > dist[i][k] + dist[k][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
    
    return dist;
}
// Compare function for min heap
int cmp(void *x, void *y){
    return ((DijHeap*)y)->weight - ((DijHeap*)x)->weight;
}
// Return minimum distance from source array
int *WGRAPH_Dijkstra(WGraph *myGraph, int src){
    Heap *myHeap;
    DijHeap cItem, nItem;
    Node *aux;
    int nr_nodes;
    int *dist, *vis;
    int i;
    nr_nodes = myGraph->nr_nodes;
    // Initialize visited array
    vis = (int*)malloc((nr_nodes + 1) * sizeof(int));
    for(i = 1; i <= nr_nodes; i++)
        vis[i] = 0;
    // Initialize distance array
    dist = (int*)malloc((nr_nodes + 1) * sizeof(int));
    for(i = 1; i <= nr_nodes; i++)
        dist[i] = INT32_MAX / 2;
    dist[src] = 0;
    // Initialize heap
    HEAP_init(&myHeap, sizeof(DijHeap));
    // Dijkstra algorithm
    cItem.node = src;
    cItem.weight = dist[src];
    HEAP_insert(myHeap, &cItem, cmp);
    while(myHeap->vect->len != 0){
        cItem = *((DijHeap*)myHeap->vect->arr);
        HEAP_remove_root(myHeap, cmp);
        vis[cItem.node] = 1;
        aux = myGraph->neighbours[cItem.node];
        while(aux != NULL){
            if(dist[aux->val] > cItem.weight + aux->weight)
                dist[aux->val] = cItem.weight + aux->weight;
            if(vis[aux->val] == 0){
                nItem.node = aux->val;
                nItem.weight = dist[aux->val];
                HEAP_insert(myHeap, &nItem, cmp);
            }
            aux = aux->next;
        }
    }
    // Free memory
    HEAP_free(&myHeap);
    free(vis);

    return dist;
}
// Return minimum distance from source array
int *WGRAPH_Bellman_Ford(WGraph *myGraph, int src){
    Node *aux;
    int nr_nodes;
    int *dist;
    int i, k;
    nr_nodes = myGraph->nr_nodes;
    // Initialize distance array
    dist = (int*)malloc((nr_nodes + 1) * sizeof(int));
    for(i = 1; i <= nr_nodes; i++)
        dist[i] = INT32_MAX / 2;
    dist[src] = 0;
    // Bellman-Ford algorithm
    for(k = 1; k < nr_nodes; k++){
        for(i = 1; i <= nr_nodes; i++){
            aux = myGraph->neighbours[i];
            while(aux != NULL){
                if(dist[aux->val] > dist[i] + aux->weight)
                    dist[aux->val] = dist[i] + aux->weight;
                aux = aux->next;
            }
        }
    }
    for(i = 1; i <= nr_nodes; i++){
        aux = myGraph->neighbours[i];
        while(aux != NULL){
            if(dist[aux->val] > dist[i] + aux->weight){
                printf("Ciclu negativ!\n");
                free(dist);
                dist = NULL;
                return dist;
            }
            aux = aux->next;
        }
    }

    return dist;
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
    for(i = 1; i <= nr_nodes; i++)
        free_list((*myGraph)->neighbours[i]);
    free((*myGraph)->neighbours);
    free(*myGraph);
    *myGraph = NULL;
}
// Return minimum distance matrix
int **WGRAPH_Johnson(WGraph *myGraph){
    int i;
    int nr_nodes;
    int **dist, *d;
    int *BF;
    Node *aux;
    nr_nodes = myGraph->nr_nodes;
    // Initialize distance matrix
    dist = genMatrix_int(nr_nodes + 1, nr_nodes + 1);
    // Johnson algorithm
    // Add new node
    myGraph->neighbours = 
    (Node**)realloc(myGraph->neighbours, (nr_nodes + 2) * sizeof(Node*));
    myGraph->neighbours[nr_nodes + 1] = NULL; 
    (myGraph->nr_nodes)++;
    // Connect new node to all other with weight 0
    for(i = 1; i <= nr_nodes; i++)
        WGRAPH_add_link(myGraph, nr_nodes + 1, i, 0);
    BF = WGRAPH_Bellman_Ford(myGraph, nr_nodes + 1);
    // Test if there are negative cicles
    if(BF == NULL){
        // Remove new node
        free_list(myGraph->neighbours[nr_nodes + 1]);
        (myGraph->nr_nodes)--;  
        dist = freeMatrix_int(dist, nr_nodes + 1);
        return dist;
    }
    // Transform weights into non-negative
    for(i = 1; i <= nr_nodes + 1; i++){
        aux = myGraph->neighbours[i];
        while(aux != NULL){
            aux->weight = aux->weight + BF[i] - BF[aux->val];
            aux = aux->next;
        }
    }
    // Remove new node
    free_list(myGraph->neighbours[nr_nodes + 1]);
    (myGraph->nr_nodes)--;
    // Dijkstra for every node
    for(i = 1; i <= nr_nodes; i++){
        d = WGRAPH_Dijkstra(myGraph, i);
        // Reweight and save result in distance array
        for(int j = 1; j <= nr_nodes; j++)
            dist[i][j] = d[j] - BF[i] + BF[j];  
        free(d);
        d = NULL;
    }
    // Free Belman-Ford distance array 
    free(BF);

    return dist;
}