#ifndef STACK_H_
#define STACK_H_
#ifndef LINKEDLIST_H_
#include "linkedlist.h"
#endif
typedef struct Stack Stack;

struct Stack {
    struct ListHead *head;
    int(*peek)(Stack *);
    int(*push)(Stack *, int);
    int(*pop)(Stack *);
    int(*size)(Stack *);
    void(*to_string)(Stack *);
    void(*stack_destroy)(Stack *);
};

struct Stack *stack_init();
int peek(Stack *my_stack);
int push(Stack *my_stack, int data);
int pop(Stack *my_stack);
int size(Stack *my_stack);
void stack_to_string(Stack *my_stack);
void stack_destroy(Stack *my_stack);

#endif // STACK_H_