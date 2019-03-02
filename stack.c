#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

struct Stack *stack_init() {
    Stack *my_stack = (Stack *)calloc(1, sizeof(Stack));
    my_stack->head = list_init();
    my_stack->peek = &peek;
    my_stack->pop = &pop;
    my_stack->push = &push;
    my_stack->size = &size;
    my_stack->to_string = &stack_to_string;
    my_stack->stack_destroy = &stack_destroy;
    return my_stack;
}

int peek(Stack *my_stack)
{
    return my_stack->head->last->data;
}

int push(Stack *my_stack, int data)
{
    return my_stack->head->add(my_stack->head, data);
}

int pop(Stack *my_stack)
{
    ListNode *temp = my_stack->head->last;
    if (temp == NULL) {
        return -1;
    }
    int data = temp->data;
    if (my_stack->head->start != my_stack->head->last) {
        my_stack->head->last = temp->prev;
        my_stack->head->last->next = NULL;
    }

    free(temp);
    return data;  
}

int size(Stack *my_stack)
{
    return my_stack->head->size(my_stack->head);;
}

void stack_to_string(Stack *my_stack)
{
    printf("Stack buttom");
    my_stack->head->to_string(my_stack->head);
    printf("Stack top");
}

void stack_destroy(Stack *my_stack) {
    my_stack->head->delete(my_stack->head);
    free(my_stack);
}
