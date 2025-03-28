#include <stdio.h>

typedef struct s_node
{
	int	value;
	struct s_node *left;
	struct s_node *right;
} 	t_node;

// prints if found
void	findnum(t_node *tree, int num)
{
	if (tree)
	{
		if (tree->value > num)
			findnum(tree->left, num);
		else if (tree->value < num)
			findnum(tree->right, num);
		else
			printf("found\n");
	}
}

typedef struct s_tree
{
	int value;
	struct s_tree *left;
	struct s_tree *right;
} t_tree;

// returns pointer to node with the value
t_tree	*find_num(t_tree *tree, int num)
{
	if (tree->value == num)
		return (tree);
	if (tree->value > num)
		return (find_num(tree->left, num));
	else
		return (find_num(tree->right, num));
}