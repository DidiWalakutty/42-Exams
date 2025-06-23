#include <limits.h>

typedef struct s_node {
	int	value;
	struct s_node *left;
	struct s_node *right;
}	t_node;

// Sum up all node values in the tree.
// Recursively add the values of the left and right subtrees to the root's value.
int	tree_add(t_node *tree)
{
	int	sum = 0;
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
