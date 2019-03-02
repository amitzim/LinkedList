// CR: The code looks great!
// CR:   1. I prefer using using 4 spaces instead of 1 tab (configurable in any text editor)
// CR:   2. You should include the .sln .vcxproj .vcxproj.filters files so other pepole cloning the repo will be able to compile / add files to the solution. These are the files that used to configure how to compile the project (replaces the makefile), so you want to keep them.
// CR:   3. You can add .gitignore file to make git ignore from the binaries in the solution directory.
#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>


int add(ListHead *lst, int data) {
	// CR: Most pepole would expect you to use malloc here, but calloc is also great.
	ListNode *new_link = (ListNode *)calloc(1, sizeof(ListNode));
	if (new_link == NULL) {
		return FAIL;
	}
	new_link->data = data;
	new_link->next = NULL;
	ListNode *temp = lst->start;
    if (temp == NULL) {
        lst->start = new_link;
        lst->last = new_link;
        return SUCCESS;
    }
	// CR: It might be better to store a pointer to the last element of the list in the "LinkedList struct" to spare this loop. Normally adding an element to a linked list is considered O(1).
	/*while (temp->next != NULL){
		temp = temp->next;
	}*/
    (lst->last)->next = new_link;
    new_link->prev = lst->last;
    lst->last = new_link;
	return SUCCESS;
}

int remove_link(ListHead *lst, int data) {
	int status = FAIL;
	ListNode *temp = lst->start;
	while (temp != NULL) {
		if (temp->data == data) {
			// delete first link
            if (temp->prev == NULL) {
                temp = temp->next;
                if (lst->start == lst->last) {
                    lst->last = temp;
                }
                free(lst->start);
                lst->start = temp;
                continue;
			// CR: I would put the } and the else in the same line. Like this:
			// CR: } else {
			// CR: But as long as you are consistent with your conventions it is great.
			}
			else {
				ListNode *new_next = NULL;
				if (temp->next != NULL) {
					new_next = temp->next;
				}
				ListNode *prev = temp->prev;
				prev->next = new_next;
				if (new_next != NULL) {
					new_next->prev = prev;
				}
                else {
                    lst->last = prev;
                }
				free(temp);
				status = SUCCESS;
				temp = prev;
			}
		}
		temp = temp->next;
	}
	
	// CR: If you don't use the counter for other purposes, it would be easier to read if you used a variable called status which is initialized to FAIL and update it to SUCCESS when you want. Counting here is just am implemetaiton detail.
	/*if (status > 0) {
		return SUCCESS;
	}
	return FAIL;*/
    return status;
}


void list_to_string(ListHead *lst) {
	ListNode *temp = lst->start;
	while (temp != NULL) {
		printf("%d ", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

// CR: name this list_destroy ?
void list_destroy(ListHead *self) {
	if (self == NULL) {
		return;
	}
    if (self->start == NULL) {
        free(self);
        return;
    }
    if (self->start != self->last){
        ListNode *temp = self->start;
        while (temp->next != NULL) {
            temp = temp->next;
            free(temp->prev);
        }
        free(temp);
    }
	free(self);
}

int list_size(ListHead *lst) {
    int counter = 0;
    ListNode *temp = lst->start;
    if (temp == NULL) {
        return counter;
    }
    while (temp != NULL) {
        counter++;
        temp = temp->next;
    }
    return counter;
}


struct ListHead *list_init() {
    ListHead *lst = (ListHead *)calloc(1, sizeof(ListHead));
    lst->start = NULL;
    lst->add = &add;
    lst->remove = &remove_link;
    lst->size = &list_size;
    lst->to_string = &list_to_string;
    lst->delete = &list_destroy;
    return lst;
}

// CR: Looks great. Now, I would suggest you to read about the linked list implementation of linux kernel.
// CR: You can read this (https://kernelnewbies.org/FAQ/LinkedLists) first, and than you can look at the actual code here
// CR: https://github.com/torvalds/linux/blob/master/include/linux/list.h
