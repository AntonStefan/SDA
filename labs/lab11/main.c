#include "WGraph.h"

int main(){
    // Open file
    FILE *read = fopen("wgraf.in", "rt");
    if(read == NULL)
        exit(1);
    
    int N, M;
    int src, dest, cost;
    int i;
    // Read number of nodes and links
    fscanf(read, "%d%d", &N, &M);
    // Initialize Graph
    WGraph *myGraph;
    WGRAPH_init(&myGraph, N);
    // Fill Graph
    for(i = 0; i < M; i++){
        fscanf(read, "%d%d%d", &src, &dest, &cost);
        if(WGRAPH_add_link(myGraph, src, dest, cost) == -1){
            WGRAPH_free(&myGraph);
            exit(2);
        }
        if(WGRAPH_add_link(myGraph, dest, src, cost) == -1){
            WGRAPH_free(&myGraph);
            exit(2);
        }
    }

    // MST with Prim
    printf("Prim:\n");
    WGRAPH_Prim(myGraph);
    printf("\n");
    // MST with Kruskal
    printf("Kruskal:\n");
    WGRAPH_Kruskal(myGraph);

    // Free memory
    WGRAPH_free(&myGraph);
    // Close file
    fclose(read);
    return 0;
}