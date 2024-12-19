typedef struct s_node
{
	int	value;
	struct s_node *left;
	struct s_node *right;
}	t_node;

// This function needs to swap the left and right child nodes
// of every node in the tree.
void	tree_swap(t_node *tree)
{
	if (!tree)
		return ;
	tree_swap(tree->left);
	tree_swap(tree->right);

	t_node *temp;
	temp = tree->left;
	tree->left = tree->right;
	tree->right = temp;	
}