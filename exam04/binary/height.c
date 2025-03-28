typedef struct s_node
{
	int value;
	struct s_node *left;
	struct s_node *right;	
}	t_node;

// The height of a binary tree is the number of edges on the longest path
// from root to leaf (last node where left and right are both NULL).
// Ononderbroken pad.
// - With each node, recursively calculate the height of its left and right subtrees.
// - Compare the larger height and add 1 (to count for the current node).
// - Recursion ends when a NULL-node is found.

// Find the longest path down.
int	height(t_node *tree)
{
	if (!tree)
		return (-1);
	int	height_left = height(tree->left);
	int	height_right = height(tree->right);

	// We need to pick the larger height, so
	// if left is >, we return 1 + height_left.
	// You pick the taller subtree and add 1 for the current node.
	if (height_left > height_right)
		return 1 + height_left;
	else
		return 1 + height_right;
}
