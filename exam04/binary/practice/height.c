typedef struct s_node
{
	int	value;
	struct s_node *left;
	struct s_node *right;
} 	t_node;

int	height(t_node *tree)
{
	if (!tree)
		return (-1);
	int left = height(tree->left);
	int right = height(tree->right);

	if (left > right)
		return (1 + left);
	else
		return (1 + right);
}