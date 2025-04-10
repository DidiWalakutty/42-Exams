#include "ft_btree.h"
#include <stdio.h>


int	main()
{
	t_btree *root = create_tree();

	printf("Original tree:\n");
	print_tree(root, 0);
}