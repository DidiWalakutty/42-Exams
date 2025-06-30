	#include "ft_list.h"
	#include <stdlib.h>

	t_list *sort_list(t_list *lst, int (*cmp)(int, int)) 
	{
		int temp;
		t_list *start = lst;

		if (!lst)
			return (NULL);

		while (lst && lst->next) 
		{
			if ((*cmp)(lst->data, lst->next->data) == 0) 
			{
				temp = lst->data;
				lst->data = lst->next->data;
				lst->next->data = temp;
				lst = start;  // Reset lst to start of list after temp
			} 
			else
				lst = lst->next;
		}
		return (start);
	}