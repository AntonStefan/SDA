#ifndef TRIE_H
#define TRIE_H
    #include <stdio.h>
    #include <stdlib.h>

    typedef struct Trie{
        int count, nrfii;
        struct Trie* child[26];
    }Trie;

    void TRIE_init(Trie **root);
    Trie *TRIE_insert(Trie *root, char *word);
    void TRIE_delete(Trie *root, char *word);
    void TRIE_free(Trie **root);
    int TRIE_is_stored(Trie *root, char *word);


#endif