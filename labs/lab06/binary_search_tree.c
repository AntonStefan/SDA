#include "binary_search_tree.h"

void BSTree_init(BSTree **root){
    *root = NULL;
}

BSTree* BSTree_insert(BSTree *root, int key){
    if(root == NULL){
        BSTree *new = (BSTree*)malloc(sizeof(BSTree));
        new->key = key;
        new->left = NULL;
        new->right = NULL;
        return new;
    }
    if(key < root->key)
        root->left = BSTree_insert(root->left, key);
    if(key > root->key)
        root->right = BSTree_insert(root->right, key);
    
    return root;
}

BSTree* BSTree_search(BSTree *root, int key){
    if(root == NULL || root->key == key)
        return root;
    if(key < root->key)
        return BSTree_search(root->left, key);
    if(key > root->key)
        return BSTree_search(root->right, key);
}

BSTree* BSTree_min_val_node(BSTree *root){
    if(root->left == NULL)
        return root;
    return BSTree_min_val_node(root->left);
}

BSTree* BSTree_delete(BSTree *root, int key){
    if(root == NULL) return root;
    else if(key < root->key) root->left = BSTree_delete(root->left, key);
    else if(key > root->key) root->right = BSTree_delete(root->right, key);
    else{
        // 0 Childrens
        if(root->left == NULL && root->right == NULL){
            free(root);
            return NULL;
        }
        BSTree *temp;
        // 1 Children
        if(root->left == NULL){
            temp = root->right;
            free(root);
            return temp;
        }
        if(root->right == NULL){
            temp = root->left;
            free(root);
            return temp;
        }
        // 2 Childrens
        temp = BSTree_min_val_node(root->right);
        root->key = temp->key;
        root->right = BSTree_delete(root->right, temp->key);
        return root;
    }

    return root;
}

void get_max_height(BSTree *root, int hTemp, int *hMax){
    if(root == NULL){
        if(hTemp > *hMax)
            *hMax = hTemp;
        return;
    }
    get_max_height(root->left, hTemp + 1, hMax);
    get_max_height(root->right, hTemp + 1, hMax);
}

int BSTree_height(BSTree *root){
    int height = 0;
    get_max_height(root, 0, &height);
    return height;
}

void BSTree_free(BSTree *root){
    if(root == NULL)
        return;
    BSTree_free(root->left);
    BSTree_free(root->right);
    free(root);
}

void BSTree_print_in_order(BSTree *root){
    if(root == NULL)
        return;
    BSTree_print_in_order(root->left);
    printf("%d ", root->key);
    BSTree_print_in_order(root->right);
}

void BSTree_print_pre_order(BSTree *root){
    if(root == NULL)
        return;
    printf("%d ", root->key);
    BSTree_print_pre_order(root->left);
    BSTree_print_pre_order(root->right);
}

void BSTree_print_post_order(BSTree *root){
    if(root == NULL)
        return;
    BSTree_print_post_order(root->left);
    BSTree_print_post_order(root->right);
    printf("%d ", root->key);
}