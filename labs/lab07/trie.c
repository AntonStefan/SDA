#include "trie.h"
#define get_number(letter) ((letter) - 97)
#define get_letter(number) ((number) + 97) 

Trie *new_node(){
    Trie *node = (Trie*)malloc(sizeof(Trie));
    node->count = 0;
    node->nrfii = 0;
    int i;
    for(i = 0; i < 26; i++){
        node->child[i] = NULL;
    }
    return node;
}

void TRIE_init(Trie **root){
    *root = new_node();
}

Trie *TRIE_insert(Trie *root, char *word){
    if(*word == '\0'){
        (root->count)++;
        return root;
    }
    if(root->child[get_number(*word)] == NULL){
        root->child[get_number(*word)] = new_node();
        (root->nrfii)++;
    }
    root->child[get_number(*word)] = TRIE_insert(root->child[get_number(*word)], word + 1);
    
    return root;
}

void TRIE_delete(Trie *root, char *word){
    if(*(word + 1) == '\0')
        if(root->child[get_number(*word)] != NULL)
            if(root->child[get_number(*word)]->count != 0)
                (root->child[get_number(*word)]->count)--;
    if(root->child[get_number(*word)] == NULL)
        return ;
    TRIE_delete(root->child[get_number(*word)], word + 1);
}

void free_memory(Trie *root){
    if(root == NULL)
        return;
    int i;
    for(i = 0; i < 26; i++)
        if(root->child[i] != NULL)
            free_memory(root->child[i]);
    free(root);
}

void TRIE_free(Trie **root){
    free_memory(*root);
    *root = NULL;
}

int TRIE_is_stored(Trie *root, char *word){
    if(*(word + 1) == '\0')
        if(root->child[get_number(*word)] != NULL)
            if(root->child[get_number(*word)]->count != 0)
                return 1;
    if(root->child[get_number(*word)] == NULL)
        return 0;
    TRIE_is_stored(root->child[get_number(*word)], word + 1);
}
