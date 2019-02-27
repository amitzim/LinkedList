#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAIL 0

typedef struct Link{
	struct Link *prev;
	struct Link *next;
	int data;
} Link;


typedef struct LinkedList {
	Link *start;
	//Functions pointers
} LinkedList;

int add(LinkedList lst, int data) {
	Link *new_link = (Link *)malloc(sizeof(Link));
	if (new_link == NULL) {
		return FAIL;
	}
	new_link->data = data;
	new_link->next = NULL;
	Link *temp = lst.start;
	if (temp == NULL) {
		lst.start = new_link;
		return SUCCESS;
	}
	while (temp->next != NULL){
		temp = temp->next;
	}
	temp->next = new_link;
	return SUCCESS;
}

int remove(LinkedList lst, int data) {
	int counter = 0;
	Link *temp = lst.start;
	while (temp != NULL) {
		if (temp->data == data) {
			// delete first link
			if (temp->prev == NULL) {
				lst.start = temp->next;
				free(temp);
				counter++;
				Link *temp = lst.start;
				temp->prev = NULL;
				continue;
			}
			else {
				Link *new_next = NULL;
				if (temp->next != NULL) {
					new_next = temp->next;
				}
				Link *prev = temp->prev;
				prev->next = new_next;
				free(temp);
				counter++;
				temp = new_next->prev;
			}
		}
		temp = temp->next;
	}
	if (counter > 0) {
		return SUCCESS;
	}
	return FAIL;
}


void to_string(LinkedList lst) {
	Link *temp = lst.start;
	while (temp != NULL) {
		printf("%d ", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

int main() {
	LinkedList lst = { NULL };
	for (int i = 1; i <= 5; i++) {
		add(lst, i);
	}
	to_string(lst);
	
	return 0;
}