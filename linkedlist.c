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
	struct Link *start;
	//Functions pointers
	int(*add)(struct LinkedList *, int);
	int(*remove)(struct LinkedList *, int);
	void(*to_string)(struct LinkedList *);
	void(*delete)();
} LinkedList;

int add(LinkedList *lst, int data) {
	Link *new_link = (Link *)calloc(1, sizeof(Link));
	if (new_link == NULL) {
		return FAIL;
	}
	new_link->data = data;
	new_link->next = NULL;
	Link *temp = lst->start;
	if (temp == NULL) {
		lst->start = new_link;
		return SUCCESS;
	}
	while (temp->next != NULL){
		temp = temp->next;
	}
	temp->next = new_link;
	new_link->prev = temp;
	return SUCCESS;
}

int remove(LinkedList *lst, int data) {
	int counter = 0;
	Link *temp = lst->start;
	while (temp != NULL) {
		if (temp->data == data) {
			// delete first link
			if (temp->prev == NULL) {
				temp = temp->next;
				free(lst->start);
				lst->start = temp;
				continue;
				/*lst->start = temp->next;
				temp->prev = NULL;
				counter++;
				Link *temp = lst->start;
				continue;*/
			}
			else {
				Link *new_next = NULL;
				if (temp->next != NULL) {
					new_next = temp->next;
				}
				Link *prev = temp->prev;
				prev->next = new_next;
				if (new_next != NULL) {
					new_next->prev = prev;
				}
				free(temp);
				counter++;
				temp = prev;
			}
		}
		temp = temp->next;
	}
	if (counter > 0) {
		return SUCCESS;
	}
	return FAIL;
}


void to_string(LinkedList *lst) {
	Link *temp = lst->start;
	while (temp != NULL) {
		printf("%d ", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

void delete_list(LinkedList *self) {
	if (self == NULL) {
		return;
	}
	Link *temp = self->start;
	while (temp->next != NULL) {
		temp = temp->next;
		free(temp->prev);
	}
	free(temp);
}

int main() {
	LinkedList *lst = (LinkedList *)calloc(1, sizeof(LinkedList));
	lst->start = NULL;
	lst->add = &add;
	lst->remove = &remove;
	lst->to_string = &to_string;
	lst->delete = &delete_list;

	for (int i = 1; i <= 20; i++) {
		lst->add(lst, i);
		lst->add(lst, 5);
		/*add(lst, 5);
		add(lst, i);*/
	}
	lst->to_string(lst);
	lst->remove(lst, 5);
	printf("HI\n");
	lst->to_string(lst);
	lst->delete(lst);
	return 0;
}