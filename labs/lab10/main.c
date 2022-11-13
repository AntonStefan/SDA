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
    }
    // Print all links
    printf("Links:\n");
    WGRAPH_print_links(myGraph);
    printf("\n");
    // Roy-Floyd
    int **dist = WGRAPH_Roy_Floyd(myGraph);
    printf("Roy-Floyd\n");
    for(i = 1; i <= myGraph->nr_nodes; i++){
        for(int j = 1; j <= myGraph->nr_nodes; j++)
            if(dist[i][j] == INT32_MAX / 2)
                printf("i ");
            else
                printf("%d ", dist[i][j]);
        printf("\n");
    }
    printf("\n");
    // Dijkstra
    printf("Dijkstra\n");
    printf("Choose source: ");
    scanf("%d", &src);
    if(src < 1 || myGraph->nr_nodes < src){
        // Free memory
        dist = freeMatrix_int(dist, myGraph->nr_nodes + 1);
        WGRAPH_free(&myGraph);
        // Close file
        fclose(read);
        exit(3);
    }  
    int *d = WGRAPH_Dijkstra(myGraph, src);
    for(i = 1; i <= myGraph->nr_nodes; i++)
        if(d[i] == INT32_MAX / 2)
            printf("i ");
        else
            printf("%d ", d[i]);
    printf("\n\n");
    free(d);
    d = NULL;
    // Bellman-Ford
    printf("Bellman-Ford\n");
    printf("Choose source: ");
    scanf("%d", &src);
    if(src < 1 || myGraph->nr_nodes < src){
        // Free memory
        dist = freeMatrix_int(dist, myGraph->nr_nodes + 1);
        WGRAPH_free(&myGraph);
        // Close file
        fclose(read);
        exit(3);
    } 
    d = WGRAPH_Bellman_Ford(myGraph, src);
    if(d != NULL){
        for(i = 1; i <= myGraph->nr_nodes; i++)
            if(d[i] == INT32_MAX / 2)
                printf("i ");
            else
                printf("%d ", d[i]);
        printf("\n\n");
    }
    // Johnson
    dist = freeMatrix_int(dist, myGraph->nr_nodes + 1);
    printf("Johnson\n");
    dist = WGRAPH_Johnson(myGraph);
    if(dist != NULL){
        for(i = 1; i <= myGraph->nr_nodes; i++){
            for(int j = 1; j <= myGraph->nr_nodes; j++)
                if(dist[i][j] == INT32_MAX / 2)
                    printf("i ");
                else
                    printf("%d ", dist[i][j]);
            printf("\n");
        }
    }
    printf("\n");
    // Free memory
    free(d);
    d = NULL;
    if(dist != NULL)
        dist = freeMatrix_int(dist, myGraph->nr_nodes + 1);
    WGRAPH_free(&myGraph);
    // Close file
    fclose(read);
    return 0;
}