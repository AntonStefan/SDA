#include "graph.h"

int main(){
    // Open file
    FILE *read = fopen("graf.in", "rt");
    if(read == NULL)
        exit(1);
    
    int N, M;
    int src, dest;
    int i;
    // Read number of nodes and links
    fscanf(read, "%d%d", &N, &M);
    // Initialize Graph
    Graph *myGraph;
    GRAPH_init(&myGraph, N);
    // Fill Graph
    for(i = 0; i < M; i++){
        fscanf(read, "%d%d", &src, &dest);
        if(GRAPH_add_link(myGraph, src, dest) == -1){
            GRAPH_free(&myGraph);
            exit(2);
        }
    }
    // Print all links
    printf("Links:\n");
    GRAPH_print_links(myGraph);
    printf("\n");
    // Get distance from node 1
    int *distance = GRAPH_distance(myGraph, 1);
    // Print distance array
    printf("Distance from node 1:\n");
    for(i = 1; i <= myGraph->nr_nodes; i++)
        printf("Node: %d - Dist: %d\n",i,  distance[i]);
    printf("\n");
    // Get topological order array
    int *topsort = GRAPH_topsort(myGraph);
    printf("Topological order:\n");
    for(i = 1; i <= myGraph->nr_nodes; i++)
        printf("%d ", topsort[i]);
    printf("\n");
    printf("\n");
    // Print strongly connected components
    printf("Strongly connected components:\n");
    GRAPH_print_SCC(myGraph);
    printf("\n");
    // Free memory
    free(topsort);
    free(distance);
    GRAPH_free(&myGraph);
    // Close file
    fclose(read);

    return 0;
}