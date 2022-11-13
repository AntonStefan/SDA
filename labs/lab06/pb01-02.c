#include "binary_search_tree.h"

int main(){

    BSTree *root;
    BSTree_init(&root);
    root = BSTree_insert(root, 25);
    root = BSTree_insert(root, 15);
    root = BSTree_insert(root, 50);
    root = BSTree_insert(root, 10);
    root = BSTree_insert(root, 22);
    root - BSTree_insert(root, 4);
    root = BSTree_insert(root, 12);
    root = BSTree_insert(root, 18);
    root = BSTree_insert(root, 24);
    root = BSTree_insert(root, 35);
    root - BSTree_insert(root, 70);
    root = BSTree_insert(root, 31);
    root - BSTree_insert(root, 44);
    root - BSTree_insert(root, 66);
    root - BSTree_insert(root, 90);
    int x;
    printf("In Order:\n");
    BSTree_print_in_order(root);
    printf("\n");
    printf("Pre Order:\n");
    BSTree_print_pre_order(root);
    printf("\n");
    printf("Post Order:\n");
    BSTree_print_post_order(root);
    printf("\n");
    printf("Search for key: ");
    scanf("%d", &x);
    BSTree *aux = BSTree_search(root, x);
    if(aux != NULL)
        printf("%d\n", aux->key);
    else
        printf("Nu exista\n");

    printf("Height: %d\n", BSTree_height(root));
    printf("Key to be deleted: ");
    scanf("%d", &x);
    root = BSTree_delete(root, x);
    printf("In Order after deletion:\n");
    BSTree_print_in_order(root);
    BSTree_free(root);

    return 0;
}