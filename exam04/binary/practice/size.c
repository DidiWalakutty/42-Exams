typedef struct s_node
{
	int	value;
	struct s_node *left;
	struct s_node *right;
} 	t_node;

int	size(t_node *tree)
{
	if (!tree)
		return (0);
	return (1 + size(tree->left) + size(tree->right));

}

// last node usually refers to rightmost leaf node
t_node *last_node(t_node *tree)
{
	if (!tree)
		return (NULL);
	while (tree->right)
		tree = tree->right;
	return (tree);
}
