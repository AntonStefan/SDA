#include "trie.h"
#include <string.h>

void number_of_words(Trie *root, int *nr);
int number_of_sim_suffix_words(Trie *root, char *word, int k);

int main(){
    FILE *read = fopen("lab7.in", "rt");
    if(read == NULL){
        printf("Eroare la deschiderea fisierului lab7.in\n");
        return 0;
    }
    char words[1000][100];
    int n, k;
    int i, j;
    int minLen = 100;
    Trie *root;
    TRIE_init(&root);

    fscanf(read, "%d%d", &n, &k);
    for(i = 0; i < n; i++){
        fscanf(read, "%s", words[i]);
        root = TRIE_insert(root, words[i]);
        if(strlen(words[i]) < minLen)
            minLen = strlen(words[i]);
    }

    if(k > minLen){
        printf("Invalid K\n");
        fclose(read);
        TRIE_free(&root);
        return 0;
    }

    for(i = 0; i < n; i++){
        for(j = 1; j <= k; j++){
            printf("%d ", number_of_sim_suffix_words(root, words[i], j));
        }
        printf("\n");
    }


    fclose(read);
    TRIE_free(&root);
    return 0;
}

void number_of_words(Trie *root, int *nr){
    if(root == NULL)
        return;
    int i;
    for(i = 0; i < 26; i++)
        if(root->child[i] != NULL)
            number_of_words(root->child[i], nr);
    (*nr) += root->count;
}

int number_of_sim_suffix_words(Trie *root, char *word, int k){
    char *wordAux = word;
    Trie *rootAux = root;
    int i, nr;
    for(i = 1; i <= k; i++){
        rootAux = rootAux->child[*wordAux - 97];
        wordAux++;
    }
    nr = 0;
    number_of_words(rootAux, &nr);
    return nr - 1;
}