#include <stdio.h>
#include <stdlib.h>

struct node_aux{
void* data;
struct node_aux* next;
};
typedef struct node_aux node;

typedef struct TList {
node* head;
int len;
} TList;

void init(TList **list);
int add(TList *list, int n, void *data);
void print_int_list(TList *list);
void free_list(TList **list);
void reverse_list(TList *list);

int main(){
    TList *list;
    init(&list);
    node *aux;
    int pos = 0;
    int n;
    int i;
    
    //Testare lista cu valori de tip int
    int v[100];
    //Citire pozitie urmata de valoare
    //Se executa doar daca pos <= lungimea listei, care initial e 0
    //si daca pos e pozitiva pana cand citim o pozitie necorespunzatoare
    printf("Pozitie Valoare\n");
    for(int i = 0; 1; i++){
        scanf("%d", &pos);
        scanf("%d", &(v[i]));
        if(add(list, pos, &(v[i])) == -1)
            break;
    }
    printf("Lista: \n");
    print_int_list(list);
    //Reverse List
    reverse_list(list);
    printf("Lista: \n");
    print_int_list(list);
    free_list(&list);
    return 0;
}

void init(TList **list){
    *list = (TList*)malloc(sizeof(TList));
    (*list)->head = NULL;
    (*list)->len = 0;
}

int add(TList *list, int n, void *data){
    if(n < 0 || n > list->len)
        return -1;
    
    int i;
    node *aux = list->head;
    node *new = (node*)malloc(sizeof(node));
    new->data = data;
    new->next = NULL;
    
    if(n == 0){
        new->next = list->head;
        list->head = new;
        (list->len)++;
        return 0;
    }

    //n > 0
    for(i = 0; i < n - 1; i++)
        aux = aux->next;
    new->next = aux->next;
    aux->next = new;
    (list->len)++;

    return 0;

}

void print_int_list(TList *list){
    node *aux = list->head;
    while(aux != NULL){
        printf("%d ", *((int*)aux->data));
        aux = aux->next;
    }
    printf("\n");
}

void reverse_list(TList *list){
    node *prev = NULL;
    node *current = list->head;
    node *next = NULL;

    while(current != NULL){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list->head = prev;

}

void free_linked_list(node *head){
    if(head == NULL)
        return;
    free_linked_list(head->next);
    free(head);
}

void free_list(TList **list){
    free_linked_list((*list)->head);
    free(*list);
    *list = NULL;
}
