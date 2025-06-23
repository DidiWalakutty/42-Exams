#include <stdio.h>

typedef struct s_node {
	int value;
	struct s_node *left;
	struct s_node *right;
} 	t_node;

// Left is smaller, right is bigger

// Prints if we found the node
void	find_num(t_node *tree, int num)
{
	if (!tree)
		return ;
	if (tree->value > num)
		find_num(tree->left, num);
	else if (tree->value < num)
		find_num(tree->right, num);
	else
		printf("found\n");
}

typedef struct s_tree
{
	int value;
	struct s_tree *left;
	struct s_tree *right;
} t_tree;

// Returns the node if we found that number
t_tree	*findnum(t_node *tree, int num)
{
	if (!tree)
		return (NULL);
	if (tree->value == num)
		return (tree);
	if (tree->value > num)
		return (findnum(tree->left, num));
	else
		return (findnum(tree->right, num));
}