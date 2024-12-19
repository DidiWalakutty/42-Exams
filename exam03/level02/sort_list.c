#include "ft_list.h"

t_list *sort_list(t_list *lst, int (*cmp)(int, int)) {
    int swap;
    t_list *start;

    start = lst;

    while (lst != NULL && lst->next != NULL) {
        if ((*cmp)(lst->data, lst->next->data) == 0) {
            swap = lst->data;
            lst->data = lst->next->data;
            lst->next->data = swap;
            lst = start;  // Reset lst to start of list after swap
        } else {
            lst = lst->next;
        }
    }
    return (start);
}