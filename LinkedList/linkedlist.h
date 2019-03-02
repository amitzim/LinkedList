#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#define SUCCESS 1
#define FAIL 0

typedef struct ListNode ListNode;
typedef struct ListHead ListHead;

// CR: a space before the {
// CR: Most pepole would call this ListNode
struct ListNode {
    struct ListNode *prev;
    struct ListNode *next;
    int data;
};

// CR: Normally this would be called ListHead
struct ListHead {
    struct ListNode *start;
    struct ListNode *last;
    // CR: It is nice that you used this exercise to also experiment with OOP in C :)
    //Functions pointers
    //struct ListHead*(*list_init)();
    int(*add)(struct ListHead *, int);
    int(*remove)(struct ListHead *, int);
    int(*size)(struct ListHead *);
    void(*to_string)(struct ListHead *);
    void(*delete)();
};

struct ListHead *list_init();
int list_size(ListHead *lst);
void list_destroy(ListHead *self);
void list_to_string(ListHead *lst);
int remove_link(ListHead *lst, int data);
int add(ListHead *lst, int data);

#endif