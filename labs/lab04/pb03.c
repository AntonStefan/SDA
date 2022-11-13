#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    void * data;
    struct node *next;
    struct node *prev;
} node;
typedef struct TDoubleLinkedList {
    node *sentinel;
    int len;
} TDoubleLinkedList;

void init(TDoubleLinkedList **list);
int add(TDoubleLinkedList *list, int pos, void *data);
void print(TDoubleLinkedList *list);
void print_reversed(TDoubleLinkedList *list);
void free_list(TDoubleLinkedList *list);

int main(){

    TDoubleLinkedList *list;
    init(&list);
    int v[100], i = 0, pos;
    int n, j;
    printf("La introducerea unei pozitii invalide programul se opreste\n");
    printf("Positie Valoare\n");
    while(1){
        scanf("%d%d", &pos, &(v[i]));
        if(add(list, pos, &(v[i])) == -1)
            break;
        i++;
    }
    printf("List:\n");
    print(list);
    printf("Reversed List:\n");
    print_reversed(list);
    //Eliberare memorie
    free_list(list);

    return 0;
}

void init(TDoubleLinkedList **list){
    *list = (TDoubleLinkedList*)malloc(sizeof(TDoubleLinkedList));
    (*list)->sentinel = (node*)malloc(sizeof(node));
    (*list)->sentinel->prev = (*list)->sentinel;
    (*list)->sentinel->next = (*list)->sentinel;
    (*list)->len = 0;
}

int add(TDoubleLinkedList *list, int pos, void *data){
    if(pos < 0 || pos > list->len)
        return -1;
    node *new = (node*)malloc(sizeof(node));
    new->data = data;
    if(pos == 0){
        new->prev = list->sentinel;
        new->next = list->sentinel->next;
        if(list->sentinel->next != list->sentinel)
            list->sentinel->next->prev = new;
        else
            list->sentinel->prev = new;
        list->sentinel->next = new;
        (list->len)++;
        return 0;
    }
    int i;
    node *aux;
    if(pos <= list->len / 2){
        aux = list->sentinel->next;
        for(i = 0; i < pos - 1; i++)
            aux = aux->next;
    }
    else{
        aux = list->sentinel->prev;
        for(i = 0; i < list->len - pos; i++)
            aux = aux->prev;
    }
    new->next = aux->next;
    new->prev = aux;
    if(pos == list->len){
        aux->next = new;
        list->sentinel->prev = new;
    }
    else{
        aux->next->prev = new;
        aux->next = new;
    }
    (list->len)++;
    return 0;
}

void print(TDoubleLinkedList *list){
    node *i;
    for(i = list->sentinel->next; i != list->sentinel; i = i->next)
        printf("%d ", *((int*)(i->data)));
    printf("\n");
}

void print_reversed(TDoubleLinkedList *list){
    node *i;
    for(i = list->sentinel->prev; i != list->sentinel; i = i->prev)
        printf("%d ", *((int*)(i->data)));
    printf("\n");
}

void freeDoubleLinkedList(node *sentinel, node *current){
    if(current == sentinel)
        return;
    freeDoubleLinkedList(sentinel, current->next);
    free(current);
}

void free_list(TDoubleLinkedList *list){
    freeDoubleLinkedList(list->sentinel, list->sentinel->next);
    free(list->sentinel);
    free(list);
}