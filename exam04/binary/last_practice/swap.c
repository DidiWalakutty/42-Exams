typedef struct s_node
{
	int	value;
	struct s_node *left;
	struct s_node *right;
} 	t_node;

void	tree_swap(t_node *tree)
{
	if (!tree)
		return ;
	tree_swap(tree->left);
	tree_swap(tree->right);

	t_node *temp = tree->left;
	tree->left = tree->right;
	tree->right = temp;
}