// CR: The code looks great!
// CR:   1. I prefer using using 4 spaces instead of 1 tab (configurable in any text editor)
// CR:   2. You should include the .sln .vcxproj .vcxproj.filters files so other pepole cloning the repo will be able to compile / add files to the solution. These are the files that used to configure how to compile the project (replaces the makefile), so you want to keep them.
// CR:   3. You can add .gitignore file to make git ignore from the binaries in the solution directory.

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAIL 0

// CR: a space before the {
// CR: Most pepole would call this ListNode
typedef struct Link{
	struct Link *prev;
	struct Link *next;
	int data;
} Link;

// CR: Normally this would be called ListHead
typedef struct LinkedList {
	struct Link *start;
	// CR: It is nice that you used this exercise to also experiment with OOP in C :)
	//Functions pointers
	int(*add)(struct LinkedList *, int);
	int(*remove)(struct LinkedList *, int);
	void(*to_string)(struct LinkedList *);
	void(*delete)();
} LinkedList;

int add(LinkedList *lst, int data) {
	// CR: Most pepole would expect you to use malloc here, but calloc is also great.
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
	// CR: It might be better to store a pointer to the last element of the list in the "LinkedList struct" to spare this loop. Normally adding an element to a linked list is considered O(1).
	while (temp->next != NULL){
		temp = temp->next;
	}
	temp->next = new_link;
	new_link->prev = temp;
	return SUCCESS;
}

int remove_link(LinkedList *lst, int data) {
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
			// CR: I would put the } and the else in the same line. Like this:
			// CR: } else {
			// CR: But as long as you are consistent with your conventions it is great.
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
	
	// CR: If you don't use the counter for other purposes, it would be easier to read if you used a variable called status which is initialized to FAIL and update it to SUCCESS when you want. Counting here is just am implemetaiton detail.
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

// CR: name this list_destroy ?
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
	free(self);
}

int main() {
	// CR: I would have create a function to do that (list_init ?) aka a constructor for a list object.
	LinkedList *lst = (LinkedList *)calloc(1, sizeof(LinkedList));
	lst->start = NULL;
	lst->add = &add;
	lst->remove = &remove_link;
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
	//free(lst);
	return 0;
}

// CR: Looks great. Now, I would suggest you to read about the linked list implementation of linux kernel.
// CR: You can read this (https://kernelnewbies.org/FAQ/LinkedLists) first, and than you can look at the actual code here
// CR: https://github.com/torvalds/linux/blob/master/include/linux/list.h
