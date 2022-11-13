
#ifndef TEMA_1_20220404_EXCEPTIONS_LIST_H
#define TEMA_1_20220404_EXCEPTIONS_LIST_H

#include "stdio.h"
#include <stdlib.h>
struct Node {
    double data;
    int timestamp;
    struct Node *next;
    struct Node *prev;
};
void append(struct Node **head_ref, double new_data, int timestamp);
void push(struct Node **head_ref, double new_data,int timestamp);
void deleteNode(struct Node** head_ref, struct Node* del);
void sortList(struct Node **head);
#endif //TEMA_1_20220404_EXCEPTIONS_LIST_H
