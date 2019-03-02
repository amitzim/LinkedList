#include "linkedlist.h"
#include "stack.h"

void check_stack() {
    Stack *st = stack_init();
    /*for (int i = 1; i <= 20; i++){
        st->push(st, i);
        printf("last element: %d\n", st->peek(st));
    }*/
    st->push(st, 1);
    st->push(st, 2);
    st->push(st, 3);
    printf("%d", st->pop(st));
    printf("%d", st->pop(st));
    printf("%d", st->pop(st));
    st->stack_destroy(st);
}

void check_list() {
    // CR: I would have create a function to do that (list_init ?) aka a constructor for a list object.
    ListHead *lst = list_init();
    /*lst->start = NULL;
    lst->add = &add;
    lst->remove = &remove_link;
    lst->to_string = &to_string;
    lst->delete = &list_destroy;*/
    printf("size at begining: %d\n", lst->size(lst));
    for (int i = 1; i <= 20; i++) {
        lst->add(lst, i);
        lst->add(lst, 5);
        //lst->remove(lst, i);
        printf("iteration %d => size is: %d\n", i, lst->size(lst));
        lst->to_string(lst);
        /*add(lst, 5);
        add(lst, i);*/
    }
    lst->to_string(lst);
    lst->remove(lst, 5);
    printf("HI\n");
    lst->to_string(lst);
    lst->delete(lst);
}

int main() {
    check_stack();
    return 0;
}
