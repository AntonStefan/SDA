#include "heap.h"
#include "time.h"

int main(){
    Heap *myHeap;
    HEAP_init(&myHeap);
    int n, x, i;
    // Citire numar de noduri
    printf("Nr of nodes: ");
    scanf("%d", &n);
    // Generare si inserare in heap
    srand(time(NULL));
    for(i = 0; i < n; i++){
        x = rand() % 1000;
        HEAP_insert(myHeap, x);
    }
    // Afisare heap in-order
    HEAP_print_inorder(myHeap->root);
    printf("\n");
    printf("\n");
    // Afisare numere in ordine descrescatoare
    for(i = 0; i < n; i++){
        printf("%d ", myHeap->root->val);
        HEAP_remove_root(myHeap);
    }
    printf("\n");
    // Eliberare memorie
    HEAP_free(&myHeap);
    return 0;
}