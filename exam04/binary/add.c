#include <limits.h>

typedef struct s_node {
	int	value;
	struct s_node *left;
	struct s_node *right;
}	t_node;

int	tree_add(t_node *tree)
{
	int	sum;
	int	sum_left = 0;
	int	sum_right = 0;

	if (!tree)
		return (0);
	sum = tree->value;
	if (tree->left)
		sum_left += tree_add(tree->left);
	if (tree->right)
		sum_right += tree_add(tree->right);
	sum = sum + sum_left + sum_right;
	return (sum);
}
