
#include "exceptions_list.h"
// insert a newNode at the end of the list

/* Given a reference (pointer to pointer) to the head of a list
   and an int, inserts a new node on the front of the list. */
void push(struct Node **head_ref, double new_data, int timestamp)
{
	struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));

	new_node->data = new_data;
	new_node->timestamp = timestamp;
	new_node->next = (*head_ref);
	new_node->prev = NULL;


	if ((*head_ref) != NULL)
		(*head_ref)->prev = new_node;

	(*head_ref) = new_node;
}
//sortList() will sort the given list in ascending order
void sortList(struct Node **head)
{
	struct Node *current = NULL, *index = NULL;
	double temp;
	//Check whether list is empty
	if(*head == NULL)
		return;
	else {
		//Current will point to head
		for(current = *head; current->next != NULL; current = current->next) {
			//Index will point to node next to current
			for(index = current->next; index != NULL; index = index->next) {
				//If current's data is greater than index's data, swap the data of current and index
				if(current->data > index->data) {
					temp = current->data;
					current->data = index->data;
					index->data = temp;
				}
			}
		}
	}
}
void append(struct Node **head_ref, double new_data, int timestamp)
{

	struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));

	struct Node *last = *head_ref;

	new_node->data = new_data;
	new_node->timestamp = timestamp;
	new_node->next = NULL;

	if (*head_ref == NULL) {
		new_node->prev = NULL;
		*head_ref = new_node;
		return;
	}

	while (last->next != NULL)
		last = last->next;

	last->next = new_node;

	new_node->prev = last;

	return;
}
void deleteNode(struct Node **head_ref, struct Node *del)
{
	/* base case */
	if (*head_ref == NULL || del == NULL)
		return;

	if (*head_ref == del)
		*head_ref = del->next;

	if (del->next != NULL)
		del->next->prev = del->prev;

	if (del->prev != NULL)
		del->prev->next = del->next;

	free(del);
	return;
}