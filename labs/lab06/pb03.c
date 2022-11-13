#include "binary_search_tree.h"

void Print_in_order_in_file(BSTree *root, FILE *write){
    if(root == NULL)
        return;
    Print_in_order_in_file(root->left, write);
    fprintf(write, "%d ", root->key);
    Print_in_order_in_file(root->right, write);
}

int main(){
    FILE *read = fopen("abc.in", "rt");
    FILE *write = fopen("abc.out", "wt");
    if(read == NULL)
        exit(1);
    BSTree *root;
    BSTree_init(&root);
    int i;
    int op, val;
    while(fscanf(read, "%d", &op) == 1){
        if(op == 0){
            Print_in_order_in_file(root, write);
            fprintf(write, "\n");
            continue;
        }
        fscanf(read, "%d", &val);
        if(op == 1)
            root = BSTree_insert(root, val);
        if(op == 2)
            root = BSTree_delete(root, val);
        if(op == 3){
            BSTree *result = BSTree_search(root, val);
            if(result == NULL)
                fprintf(write, "Valoare negasita!\n");
            else
                fprintf(write, "Valoare gasita!\n");
        }
    }

    fclose(read);
    fclose(write);
    BSTree_free(root);
    return 0;
}