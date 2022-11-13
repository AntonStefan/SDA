#include "trie.h"

int main(){
    Trie *root;
    TRIE_init(&root);
    
    root = TRIE_insert(root, "abcd");
    root = TRIE_insert(root, "abc");
    root = TRIE_insert(root, "ab");
    root = TRIE_insert(root, "zed");
    
    printf("ab: %d\n", TRIE_is_stored(root, "ab"));
    printf("abc: %d\n", TRIE_is_stored(root, "abc"));
    printf("abcd: %d\n", TRIE_is_stored(root, "abcd"));
    printf("zed: %d\n", TRIE_is_stored(root, "zed"));

    TRIE_delete(root, "abcd");
    TRIE_delete(root, "ab");
    TRIE_delete(root, "z");
    TRIE_delete(root, "zed");

    printf("ab: %d\n", TRIE_is_stored(root, "ab"));
    printf("abc: %d\n", TRIE_is_stored(root, "abc"));
    printf("abcd: %d\n", TRIE_is_stored(root, "abcd"));
    printf("zed: %d\n", TRIE_is_stored(root, "zed"));

    TRIE_free(&root);
    return 0;
}