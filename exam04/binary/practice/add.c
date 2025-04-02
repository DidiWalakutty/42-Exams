typedef struct s_node
{
	int value;
	struct s_node *left_tree;
	struct s_node *right_tree;
}	t_node;

int	tree_add(t_node *tree)
{
	if (!tree)
		return (0);
	int sum = 0;
	int left = 0;
	int right = 0;

	sum = tree->value;
	if (tree->left_tree)
		left += tree_add(tree->left_tree);
	if (tree->right_tree)
		right += tree_add(tree->right_tree);
	sum = sum + left + right;
	return (sum);
}