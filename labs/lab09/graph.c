#include "graph.h"
// Initialize graph
void GRAPH_init(Graph **graph, int nr_nodes){
    *graph = (Graph*)malloc(sizeof(Graph));
    (*graph)->nr_nodes = nr_nodes;
    (*graph)->neighbours = (Node**)malloc((nr_nodes + 1) * sizeof(Node*));
    int i;
    for(i = 0; i <= nr_nodes; i++)
        (*graph)->neighbours[i] = NULL;
}
// Add link to the graph
int GRAPH_add_link(Graph *graph, int src, int dest){
    if(graph->neighbours[src] == NULL){
        graph->neighbours[src] = (Node*)malloc(sizeof(Node));
        if(graph->neighbours[src] == NULL)
            return -1;
        graph->neighbours[src]->val = dest;
        graph->neighbours[src]->next = NULL;
        return 0;
    }
    Node *aux = graph->neighbours[src];
    while(aux->next != NULL){
        aux = aux->next;
    }
    aux->next = (Node*)malloc(sizeof(Node));
    if(aux->next == NULL)
        return -1;
    aux->next->val = dest;
    aux->next->next = NULL;
    return 0;
}
// Print all links in the graph
void GRAPH_print_links(Graph *graph){
    Node *aux;
    int i;
    for(i = 1; i <= graph->nr_nodes; i++){
        printf("%d-> ", i);
        aux = graph->neighbours[i];
        while(aux != NULL){
            printf("%d ", aux->val);
            aux = aux->next;
        }
        printf("\n");
    }
}
// Generate the distance array
void BFS_distance(Graph *graph, Queue *q, int *distance, int *visited){
    if(is_empty_queue(q) == 1)
        return;
    int currNode = q->head->data.val1;
    int currDist = q->head->data.val2;
    Node *aux = graph->neighbours[currNode];
    while(aux != NULL){
        if(visited[aux->val] == 0){
            add_queue(q, aux->val, currDist + 1);
            visited[aux->val] = 1;
            distance[aux->val] = currDist + 1;
        }
        aux = aux->next;
    }
    pop_queue(q);
    BFS_distance(graph, q, distance, visited);
}
// Return array with the distance from start to other nodes
int *GRAPH_distance(Graph *graph, int start){
    Queue *q;
    int *distance;
    int *visited;
    int i;
    // Initialize data
    init_queue(&q);
    distance = (int*)malloc((graph->nr_nodes + 1) * sizeof(int));
    visited = (int*)calloc(graph->nr_nodes + 1, sizeof(int));
    for(i = 1; i <= graph->nr_nodes; i++)
        distance[i] = -1;
    // Setup BFS
    add_queue(q, start, 0);
    distance[start] = 0;
    visited[start] = 1;
    
    BFS_distance(graph, q, distance, visited);
    
    //Free memory
    free(visited);
    free_queue(&q);
    return distance;
}
// Generate topological order array
void DFS_topsort(Graph *graph, int cNode, int *visited, int *topsort, int *k){
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
int *GRAPH_topsort(Graph *graph){
    int *topsort;
    int *visited;
    int i;
    int k;
    topsort = (int*)malloc((graph->nr_nodes + 1) * sizeof(int));
    visited = (int*)calloc(graph->nr_nodes + 1, sizeof(int));
    k = graph->nr_nodes;
    for(i = 1; i <= graph->nr_nodes; i++)
        if(visited[i] == 0)
            DFS_topsort(graph, i, visited, topsort, &k);

    free(visited);
    return topsort;
}
// free node list
void free_list(Node *root){
    if(root == NULL)
        return;
    free_list(root->next);
    free(root);
}
// Free graph memory
void GRAPH_free(Graph **graph){
    int nr_nodes;
    int i;
    nr_nodes = (*graph)->nr_nodes;
    for(i = 1; i <= nr_nodes; i++)
        free_list((*graph)->neighbours[i]);
    free((*graph)->neighbours);
    free(*graph);
    *graph = NULL;
}
// Print nodes by DFS
void DFS_print(Graph *graph, int cNode, int *visited){
    if(visited[cNode] == 1)
        return;
    visited[cNode] = 1;
    Node *aux = graph->neighbours[cNode];
    while(aux != NULL){
       DFS_print(graph, aux->val, visited);
       aux = aux->next;
    }
    printf("%d ", cNode);
}
// Return transpose graph
Graph *GRAPH_transpose(Graph *graph){
    Graph *tGraph;
    Node *aux;
    int i;
    GRAPH_init(&tGraph, graph->nr_nodes);
    tGraph->nr_nodes = graph->nr_nodes;
    for(i = 1; i <= graph->nr_nodes; i++){
        aux = graph->neighbours[i];
        while(aux != NULL){
            GRAPH_add_link(tGraph, aux->val, i);
            aux = aux->next;
        }
    }
    return tGraph;
}
// Print strongly connected components
void GRAPH_print_SCC(Graph *graph){
    int *topsort = GRAPH_topsort(graph);
    int *visited = (int*)calloc(graph->nr_nodes + 1, sizeof(int));
    int i;
    Graph *tGraph = GRAPH_transpose(graph);

    for(i = 1; i <= tGraph->nr_nodes; i++){
        if(visited[topsort[i]] == 0){
            DFS_print(tGraph, topsort[i], visited);
            printf("\n");
        }
    }
    
    GRAPH_free(&tGraph);
    free(visited);
    free(topsort);
}