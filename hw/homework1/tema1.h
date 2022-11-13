

#ifndef TEMA_1_20220404_TEMA1_H
#define TEMA_1_20220404_TEMA1_H

#include "stdio.h"
#include <stdlib.h>
#include "string.h"
#include <unistd.h>
#include <math.h>
#include "exceptions_list.h"

void create_struct(struct Node **head, int *elements_number);
void eliminate_exceptions(struct Node** head, int *elements_number);
void eliminate_noise(struct Node **head, int *elements_number);
void eliminate_noise_average(struct Node **head, int *elements_number);
void uniformise(struct Node **head, int elements_number);
void statistics(struct Node *head, int range,int*statistic);
void complete(struct Node **head);
#endif //TEMA_1_20220404_TEMA1_H
