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
	
	int cur = tree->value;
	int left = smallest(tree->left);
	int right = smallest(tree->right);

	if (left < cur)
		cur = left;
	if (right < cur)
		cur = right;
	return (cur);
}

t_node *smallest(t_node *tree)
{
	if (!tree)
		return (NULL);
	t_node *current = tree;
	t_node *left = smallest(tree->left);
	t_node *right = smallest(tree->right);

	if (left && left->value < current->value)
		current = left;
	if (right && right->value < current->value)
		current = right;
	return (current);
}