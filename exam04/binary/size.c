typedef struct s_node
{
	int	value;
	struct s_node *left;
	struct s_node *right;
}	t_node;

// Counts the numbers of nodes in the tree.
// Recursively counts left and right subtrees and adds 1 for the current node.
int	size(t_node *tree)
{
	if (!tree)
		return (0);
	return (1 + size(tree->left) + size(tree->right));
}