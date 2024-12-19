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
	int	cur = tree->value;
	// calling biggest_num recursively, where each node
	// goes into a seperate biggest_num function.
	// Each call operates only on that node and its left and right subtrees.
	// Each function call computes the largest value in its own subtree and
	// calculates the lagest value during backtracking (it bubbles up).
	int	left = biggest_num(tree->left);
	int	right = biggest_num(tree->right);

	// The left tree is usually the tree that contains smaller values than the node
	// we compare it too.
	if (left > cur)
		cur = left;
	if (right > cur)
		cur = right;
	return (cur);
}