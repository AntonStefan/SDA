#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    void * data;
    struct node *next;
    struct node *prev;
} node;
typedef struct TDoubleLinkedList {
    node *head;
    node *tail;
    int len;
} TDoubleLinkedList;

void init(TDoubleLinkedList **list);
int add(TDoubleLinkedList *list, int pos, void *data);
int remove_pos(TDoubleLinkedList *list, int pos);
void print(TDoubleLinkedList *list);
void print_reversed(TDoubleLinkedList *list);
void free_list(TDoubleLinkedList *list);
//Problema 2
void add_in_order(TDoubleLinkedList *list, void *data);
//Problema 4
void switchData(node *a, node *b);
void sortList(TDoubleLinkedList *list);

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
    print(list);
    printf("Positie de sters\n");
    while(1){
        scanf("%d", &pos);
        if(remove_pos(list, pos) == -1)
            break;
    }
    printf("List:\n");
    print(list);
    printf("Reversed:\n");
    print_reversed(list);
    //Testare functie problema 2
    printf("Numar de valori: ");
    scanf("%d", &n);
    printf("Valoare\n");
    for(j = 0; j < n; j++){
        scanf("%d", &(v[i]));
        add_in_order(list, &(v[i]));
        if(v[i] == -10)
            break;
        i++;
    }
    printf("List:\n");
    print(list);
    //Testare functie problema 2
    sortList(list);
    printf("Sorted List:\n");
    print(list);
    //Eliberare memorie
    free_list(list);

    return 0;
}

void init(TDoubleLinkedList **list){
    *list = (TDoubleLinkedList*)malloc(sizeof(TDoubleLinkedList));
    (*list)->head = NULL;
    (*list)->tail = NULL;
    (*list)->len = 0;
}

int add(TDoubleLinkedList *list, int pos, void *data){
    if(pos < 0 || pos > list->len)
        return -1;
    node *new = (node*)malloc(sizeof(node));
    new->data = data;
    if(pos == 0){
        new->prev = NULL;
        new->next = list->head;
        if(list->head != NULL)
            list->head->prev = new;
        else
            list->tail = new;
        list->head = new;
        (list->len)++;
        return 0;
    }
    int i;
    node *aux;
    if(pos <= list->len / 2){
        aux = list->head;
        for(i = 0; i < pos - 1; i++)
            aux = aux->next;
    }
    else{
        aux = list->tail;
        for(i = 0; i < list->len - pos; i++)
            aux = aux->prev;
    }
    new->next = aux->next;
    new->prev = aux;
    if(pos == list->len){
        aux->next = new;
        list->tail = new;
    }
    else{
        aux->next->prev = new;
        aux->next = new;
    }
    (list->len)++;
    return 0;
}

int remove_pos(TDoubleLinkedList *list, int pos){
    if(pos < 0 || pos >= list->len)
        return -1;
    node *delete;
    if(pos == 0){
        delete = list->head;
        if(list->head->next == NULL){
            list->head = NULL;
            list->tail = NULL;
        }
        else{
            list->head = list->head->next;
            list->head->prev = NULL;
        }
        free(delete);
        (list->len)--;
        return 0;
    }
    int i;
    node *aux = list->head;
    for(i = 0; i < pos - 1; i++)
        aux = aux->next;
    delete = aux->next;
    aux->next = delete->next;
    if(delete->next == NULL)
        list->tail = aux;
    else
        delete->next->prev = aux;
    free(delete);
    (list->len)--;
    return 0;
}

void print(TDoubleLinkedList *list){
    if(list->len == 0)
        return ;
    node *i;
    for(i = list->head; i != list->tail; i = i->next)
        printf("%d ", *((int*)(i->data)));
    printf("%d ", *((int*)(i->data)));
    printf("\n");
}

void print_reversed(TDoubleLinkedList *list){
    if(list->len == 0)
        return ;
    node *i;
    for(i = list->tail; i != list->head; i = i->prev)
        printf("%d ", *((int*)(i->data)));
    printf("%d ", *((int*)(i->data)));
    printf("\n");
}

void freeDoubleLinkedList(node *current){
    if(current == NULL)
        return;
    freeDoubleLinkedList(current->next);
    free(current);
}

void free_list(TDoubleLinkedList *list){
    freeDoubleLinkedList(list->head);
    free(list);
}

void add_in_order(TDoubleLinkedList *list, void *data){
    int pos = 0;
    node *aux = list->head;
    while(aux != NULL){
        if(*(int*)data < *(int*)(aux->data))
            break;
        aux = aux->next;
        pos++;
    }
    add(list, pos, data);
}

void switchData(node *a, node *b){
    void *aux;
    aux = a->data;
    a->data = b->data;
    b->data = aux;
}

void sortList(TDoubleLinkedList *list){
    node *i, *j;
    for(i = list->head; i != NULL; i = i->next)
        for(j = i->next; j != NULL; j = j->next)
            if(*(int*)i->data > *(int*)j->data)
                switchData(i, j);   
}