#include "generic_heap.h"

typedef struct HuffNode {
    char ch;
    int val;
    struct HuffNode *left, *right;
}HuffNode;

int cmp(void* item1, void* item2);
HuffNode *new_node();
void print_code(HuffNode *root, char *code, char *initCode);
void free_memory(HuffNode *root);

int main(){
    // Deschidere fisier
    FILE *read = fopen("huff.in", "rt");
    if(read == NULL)
        exit(1);
    //Initializare heap
    Heap *heap;
    HEAP_init(&heap, sizeof(HuffNode));

    HuffNode newNode;
    newNode.left = NULL;
    newNode.right = NULL;
    char ch;
    int val;
    int n, i;
    // Citire date
    fscanf(read, "%d", &n);
    fgetc(read);
    for(i = 0; i < n; i++){
        fscanf(read, "%c", &ch);
        fscanf(read, "%d", &val);
        fgetc(read);
        newNode.ch = ch;
        newNode.val = val;
        HEAP_insert(heap, &newNode, cmp);
    }
    // Generare arbore Huffman
    HuffNode leftNode, rightNode;
    while(heap->vect->len > 1){
        leftNode = *((HuffNode*)VECTOR_get_item(heap->vect, 0));
        HEAP_remove_root(heap, cmp);
        rightNode = *((HuffNode*)VECTOR_get_item(heap->vect, 0));
        HEAP_remove_root(heap, cmp);
        newNode.left = new_node();
        newNode.right = new_node();
        *(newNode.left) = leftNode;
        *(newNode.right) = rightNode;
        newNode.ch = 0;
        newNode.val = newNode.left->val + newNode.right->val;
        HEAP_insert(heap, &newNode, cmp);
    }
    newNode = *((HuffNode*)VECTOR_get_item(heap->vect, 0));
    HEAP_remove_root(heap, cmp);
    // Afisare litere cu noile coduri binare
    char code[100];
    print_code(&newNode, code, code);
    // Eliberare memorie
    free_memory(newNode.left);
    free_memory(newNode.right);
    HEAP_free(&heap);
    fclose(read);
    return 0;
}
// Functie de commparare pentru heap ul generic
int cmp(void* item1, void* item2){
    return ((HuffNode*)item2)->val - ((HuffNode*)item1)->val;
}
// Creare nod nou
HuffNode *new_node(){
    HuffNode *node = (HuffNode*)malloc(sizeof(HuffNode));
    node->ch = 0;
    node->val = 0;
    node->left = NULL;
    node->right = NULL;
}
// Afiseaza literele si noul lor cod binar
void print_code(HuffNode *root, char *code, char *initCode){
    if(root == NULL)
        return;
    if(root->ch != 0){
        *code = '\0';
        printf("%c %s\n", root->ch, initCode);
    }
    *code = '0';
    print_code(root->left, code + 1, initCode);
    *code = '1';
    print_code(root->right, code + 1, initCode);
}
// Elibereaza memoria din arborele cu radacina root
void free_memory(HuffNode *root){
    if(root == NULL)
        return;
    free_memory(root->left);
    free_memory(root->right);
    free(root);
}