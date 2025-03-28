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
	int height_left = height(tree->left);
	int height_right = height(tree->right);

	if (height_left > height_right)
		return (1 + height_left);
	else
		return (1 + height_right);
}