#include <limits.h>

typedef struct s_node
{
	int	value;
	struct s_node *left;
	struct s_node *right;
} 	t_node;

int biggest_num(t_node *tree)
{
	if (!tree)
		return (INT_MIN);
	int max = tree->value;
	int left = biggest_num(tree->left);
	int right = biggest_num(tree->right);

	if (left > max)
		max = left;
	if (right > max)
		max = right;
	return (max);
}

t_node *biggestnum(t_node *tree)
{
	if (!tree)
		return (NULL);
	t_node *max = tree;
	t_node *left = biggestnum(tree->left);
	t_node	*right = biggestnum(tree->right);

	if (left && left->value > max->value)
		max = left;
	if (right && right->value > max->value)
		max = right;
	return (max);
}