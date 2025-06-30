#include "ft_list.h"
#include <stdlib.h>

void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	if (!begin_list || !*begin_list)
		return ;

	t_list *current = *begin_list;
	t_list *previous = NULL;
	t_list *next = NULL;

	while (current)
	{
		next = current->next;
		if ((*cmp)(current->data, data_ref) == 0)
		{
			if (previous == NULL)
				*begin_list = next;
			else
				previous->next = next;
			free(current);
		}
		else
			previous = current;
		current = next;
	}
}