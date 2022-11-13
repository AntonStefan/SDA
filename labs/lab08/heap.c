#include "heap.h"
// Initialize heap
void HEAP_init(Heap **heap){
    *heap = (Heap*)malloc(sizeof(Heap));
    (*heap)->no_nodes = 0;
    (*heap)->root = NULL;
}
// Create and initialize new node
node *new_node(int val){
    node *newNode = (node*)malloc(sizeof(node));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->val = val;
}
// Return the first level in which a value can be inserted
int get_available_level(node *root){
    int level = 0;
    while(root != NULL){
        level++;
        root = root->right;
    }
    return level;
}
// Fast swap
void swap(int *x, int *y){
    *x = *x ^ *y;
    *y = *x ^ *y;
    *x = *x ^ *y;
}
// Insert value in heap
void HEAP_insert(Heap *heap, int val){
    node* newNode = new_node(val);
    node* aux = heap->root;
    int avLevel = get_available_level(heap->root);
    int new_no_nodes = heap->no_nodes + 1;
    int mask = 1 << (avLevel - 1);
    int i;
    // Empty heap
    if(heap->no_nodes == 0){
        heap->root = newNode;
        (heap->no_nodes)++;
        return;
    }
    // Non-empty heap
    for(i = 0; i < avLevel - 1; i++){
        if(aux->val < newNode->val)
            swap(&(aux->val), &(newNode->val));
        if(new_no_nodes & mask)
            aux = aux->right;
        else
            aux = aux->left;
        mask = mask >> 1;
    }
    if(aux->val < newNode->val)
        swap(&(aux->val), &(newNode->val));
    if(new_no_nodes & mask)
        aux->right = newNode;
    else
        aux->left = newNode;
    (heap->no_nodes)++;
}
// Return level on which a node is stored in heap
int get_node_level(int node_nr){
    if(node_nr <= 0)
        return -1;
    int level = 0;
    int pow = 1;
    while(node_nr >= pow){
        pow *= 2;
        level++;
    }
    return level - 1;
}
// Return pointer to the last node in heap
node *get_last_node_parent(Heap *heap){
    int level = get_node_level(heap->no_nodes);
    if(level <= 0)
        return NULL;
    node* aux = heap->root;
    int mask = 1 << (level - 1);
    int i;
    for(i = 0; i < level - 1; i++){
        if(heap->no_nodes & mask)
            aux = aux->right;
        else
            aux = aux->left;
        mask = mask >> 1;
    }
    return aux;
}
// If only the root is misplaced it will correct the heap
void HEAP_heapify(Heap *heap){
    node* aux = heap->root;
    while(1){
        if(aux->right == NULL)
            break;
        if(aux->left->val > aux->right->val){
            if(aux->left->val > aux->val){
                swap(&(aux->val), &(aux->left->val));
                aux = aux->left;
            }
            else
                break;
        }
        else{
            if(aux->right->val > aux->val){
                swap(&(aux->val), &(aux->right->val));
                aux = aux->right;
            }
            else
                break;
        }
    }
    if(aux->left != NULL && aux->left->val > aux->val)
        swap(&(aux->val), &(aux->left->val));
}
// Remove the root node
void HEAP_remove_root(Heap *heap){
    if(heap->no_nodes == 1){
        (heap->no_nodes)--;
        free(heap->root);
        heap->root = NULL;
        return;
    }
    node *lastNodeParent = get_last_node_parent(heap);
    if(lastNodeParent->right != NULL){
        swap(&(heap->root->val), &(lastNodeParent->right->val));
        free(lastNodeParent->right);
        lastNodeParent->right = NULL;
    }
    else{
        swap(&(heap->root->val), &(lastNodeParent->left->val));
        free(lastNodeParent->left);
        lastNodeParent->left = NULL;
    }
    (heap->no_nodes)--;
    // Fix the heap
    HEAP_heapify(heap);
}
// Print heap inorder
void HEAP_print_inorder(node *root){
    if(root == NULL)
        return;
    HEAP_print_inorder(root->left);
    printf("%d ", root->val);
    HEAP_print_inorder(root->right);
}
// Free heap nodes
void free_memory(node *root){
    if(root == NULL)
        return;
    free_memory(root->left);
    free_memory(root->right);
    free(root);
}
// Free heap
void HEAP_free(Heap **heap){
    free_memory((*heap)->root);
    free(*heap);
}