

#include "tema1.h"

void eliminate_noise(struct Node **head, int *elements_number) //e2 filtru median
{
	struct Node *current = NULL;
	current = *head;
	int total_noise_elements = 0;
	struct Node *noise_head = NULL;
	int i = 0;

	for (i = 0; i < *elements_number - 2; i++) {
		if (i > 1) {
			struct Node *temp_head = NULL;
			append(&temp_head, current->prev->prev->data, current->prev->prev->timestamp);
			append(&temp_head, current->prev->data, current->prev->timestamp);
			append(&temp_head, current->data, current->timestamp);
			append(&temp_head, current->next->data, current->next->timestamp);
			append(&temp_head, current->next->next->data, current->next->next->timestamp);
			sortList(&temp_head);
			append(&noise_head, temp_head->next->next->data,
				   temp_head->next->next->timestamp);
			total_noise_elements++;
			struct Node *current_noise = temp_head;
			while (current_noise != NULL) {
				struct Node *temp = current_noise;
				current_noise = current_noise->next;
				free(temp);
			}
		}
		current = current->next;
	}
	current = *head;
	while (current != NULL) {
		struct Node *temp = current;
		current = current->next;
		free(temp);
	}
	*elements_number = total_noise_elements;
	*head = noise_head;
}
void eliminate_noise_average(struct Node **head, int *elements_number) //e3 filtru median prin medie aritmetica
{
	struct Node *current = NULL;
	current = *head;
	int total_noise_elements = 0;
	struct Node *noise_head = NULL;
	int i = 0;

	for (i = 0; i < *elements_number - 2; i++) {
		if (i > 1) {
			double first_number = current->prev->prev->data;
			double second_number = current->prev->data;
			double third_number = current->next->data;
			double fourth_number = current->next->next->data;
			double current_number = current->data;
			double average = (first_number + second_number + third_number + fourth_number +
							  current_number) / 5.0;
			append(&noise_head, average, current->timestamp);
			total_noise_elements++;
		}
		current = current->next;
	}
	current = *head;
	while (current != NULL) {
		struct Node *temp = current;
		current = current->next;
		free(temp);
	}
	*elements_number = total_noise_elements;
	*head = noise_head;
}
void eliminate_exceptions(struct Node **head, int *elements_number) //e1
{
	struct Node *current = NULL;
	struct Node *new_head = NULL;
	int added = 0;
	current = *head; 
	append(&new_head, current->data, current->timestamp);
	append(&new_head, current->next->data, current->next->timestamp);
	int power = 2;
	double k = 5.00;
	int i = 0;

	for (i = 0; i < *elements_number - 2; i++) {
		if (i > 1) {
			double first_number = current->prev->prev->data;
			double second_number = current->prev->data;
			double third_number = current->next->data;
			double fourth_number = current->next->next->data;
			double current_number = current->data;
			double average = (first_number + second_number + third_number + fourth_number +
							  current_number) / k;
			double deviation = sqrt((pow(first_number - average,
										 power) + pow(second_number - average, power) +
									 pow(third_number - average, power) + pow(fourth_number - average, power) +
									 pow(current_number - average, power)) / k);
			if (current_number >= (average - deviation) &&
					current_number <= (average + deviation)) {
				append(&new_head, current->data, current->timestamp);
				added++; //daca numarul apartine intrevavlui adaugam 5 elemente
			}
		}
		current = current->next;
	}
	append(&new_head, current->data, current->timestamp);
	append(&new_head, current->next->data, current->next->timestamp);
	*elements_number = added + 4;
	current = *head;
	while (current != NULL) {
		struct Node *temp = current;
		current = current->next;
		free(temp);
	}
	*head = new_head;
}
void uniformise(struct Node **head, int elements_number) //u
{
	struct Node *current = NULL;
	struct Node *prev = NULL;
	current = *head;
	prev = current->prev;
	int i = 0;

	for (i = 0; i < elements_number; i++) {
		if (i > 0 && (current->timestamp - prev->timestamp) >= 100 &&
				(current->timestamp - prev->timestamp) <= 1000) {
			current->timestamp = (prev->timestamp + current->timestamp) / 2;
			current->data = (current->data + prev->data) / 2;
		}
		current = current->next;
		if(current)
			prev = current->prev;
	}
}
void create_struct(struct Node **head, int *elements_number)
{
	char str[60];
	char *eptr = NULL;
	fgets(str, 60, stdin);
	*elements_number = atoi(str);
	int i = 0;

	for (i = 0; i < *elements_number; i++) {
		fgets(str, 60, stdin);
		double value;
		int timestamp;
		char *token;
		token = strtok(str, " ");
		timestamp = atoi(token);
		token = strtok(NULL, " ");
		value = strtod(token, &eptr); //string to double
		append(head, value, timestamp);
	}
}
void statistics(struct Node *head, int range, int *statistic) //st
{
	sortList(&head);
	int first = 0;
	int elements_number = 0;
	int second = 0;
	struct Node *current = head;
	first = (int)floor(current->data);
	second = first + range;
	while (current != NULL) {
		while (current != NULL &&  current->data >= first && current->data <= second) {
			elements_number++;
			current = current->next;
		}
		if(elements_number != 0)
			printf("[%d, %d] %d\n", first, second, elements_number);
		elements_number = 0;
		first = second;
		second = first + range;
	}
	*statistic = 1;
}
void complete(struct Node **head) //c
{
	struct Node *current = *head;
	struct Node *prev = current->prev;
	double w[] = {0.07, 0.23, 0.70};
	int i = 0;

	while (current != NULL) {
		if(i > 0 && (current->timestamp - prev->timestamp) > 1000) {
			while ((current->timestamp - prev->timestamp) > 200) {
				struct Node *lefties[] = {prev->prev->prev, prev->prev, prev};
				struct Node *righties[] = {current, current->next, current->next->next};
				struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
				new_node->timestamp = prev->timestamp + 200;
				double right_term = 0;
				double left_term = 0;
				double C = ((double)new_node->timestamp - (double)lefties[2]->timestamp) / ((
							   double)righties[0]->timestamp - (double)lefties[2]->timestamp);
				printf("%f\n", C);
				for(int j = 0; j < 3; j++) {
					left_term += (lefties[j]->data * w[j]);
					right_term += (righties[j]->data * w[j]);
				}
				new_node->data = (1.0 - C) * left_term + C * right_term;
				new_node->next = current;
				new_node->prev = prev;
				current->prev = new_node;
				prev->next = new_node;
				prev = new_node;
				printf(" %d %f\n", new_node->timestamp, new_node->data);
			}
		}
		prev = current;
		current = current->next;
		i++;
	}
}
int main(int argc, char *argv[])
{
	struct Node *head = NULL;
	int elements_number = 0;
	int statistc = 0;
	create_struct(&head, &elements_number);
	int i = 0;

	for (i = 1; i < argc; i++) {
		if (strstr(argv[i], "e1"))
			eliminate_exceptions(&head, &elements_number);
		else if (strstr(argv[i], "e2"))
			eliminate_noise(&head, &elements_number);
		else if(strstr(argv[i], "e3"))
			eliminate_noise_average(&head, &elements_number);
		else if(strstr(argv[i], "u"))
			uniformise(&head, elements_number);
		else if(strstr(argv[i], "st"))
			statistics(head, atoi(argv[i] + 4), &statistc);
		else if(strstr(argv[i], "c"))
			complete(&head);
	}
	if(statistc == 0) {
		struct Node *current = head;
		printf("%d\n", elements_number);
		while (current != NULL) {
			struct Node *temp = current;
			printf("%d %.2lf\n", current->timestamp, current->data);
			current = current->next;
			free(temp);
		}
	} else {
		struct Node *current = head;
		while (current != NULL) {
			struct Node *temp = current;
			current = current->next;
			free(temp);
		}
	}
	fflush(stdout);
}