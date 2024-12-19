#include <stdio.h>

typedef struct s_node {
	int value;
	struct s_node *left;
	struct s_node *right;
} 	t_node;

void	find_num(t_node *tree, int num)
{
	if (tree)
	{
		// The current value is too big for num, so let's search
		// in the left (smaller values) tree.
		if (tree->value > num)
			find_num(tree->left, num);
		// The current value is too small for num, so let's search
		// in the right (bigger values) tree.
		else if (tree->value < num)
			find_num(tree->right, num);
		else
			printf("found\n");
	}
}
