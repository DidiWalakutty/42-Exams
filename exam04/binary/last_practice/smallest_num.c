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
	t_node *cur = tree;
	t_node *left = smallest(tree->left);
	t_node *right = smallest(tree->right);

	if (left && left->value < cur->value)
		cur = left;
	if (right && right->value < cur->value)
		cur = right;
	return (cur);
}