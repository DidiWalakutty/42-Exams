#include <limits.h>

typedef struct s_node
{
	int	value;
	struct s_node *left;
	struct s_node *right;
} 	t_node;

int smallest(t_node *tree)
{
	if (!tree)
		return (INT_MAX);
	int small = tree->value;
	int left = smallest(tree->left);
	int right = smallest(tree->right);

	if (left < small)
		small = left;
	if (right < small)
		small = right;
	return (small);
}