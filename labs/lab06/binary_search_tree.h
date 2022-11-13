#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE
    #include <stdio.h>
    #include <stdlib.h>

    typedef struct BSTree {
    int key;
    struct BSTree *left, * right;
    } BSTree;

    void BSTree_init(BSTree **root);
    BSTree* BSTree_insert(BSTree *root, int key);
    BSTree* BSTree_search(BSTree *root, int key);
    BSTree* BSTree_min_val_node(BSTree *root);
    BSTree* BSTree_delete(BSTree *root, int key);
    int BSTree_height(BSTree *root);
    void BSTree_free(BSTree *root);

    void BSTree_print_in_order(BSTree *root);
    void BSTree_print_pre_order(BSTree *root);
    void BSTree_print_post_order(BSTree *root);

#endif