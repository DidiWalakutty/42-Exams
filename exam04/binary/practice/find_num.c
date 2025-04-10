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
			find_num(tree->left, num);
		if (tree->value < num)
			find_num(tree->right, num);
		else	
			printf("Found\n");
	}
}

/*
	Uncertain of which kind the exam gives
*/

typedef struct s_tree
{
	int value;
	struct s_tree *left;
	struct s_tree *right;
} t_tree;

// returns pointer to node with the value
t_tree	*find_num(t_tree *tree, int num)
{
	if (!tree)
		return (NULL);
	if (tree->value == num)
		return (tree);
	if (tree->value > num)
		return (find_num(tree->left, num));
	if (tree->value < num)
		return (find_num(tree->right, num));
	return (NULL);
}

// if unsorted:
t_tree *find_num(t_tree *tree, int num)
{
	if (!tree)
		return (NULL);
	if (tree->value == num)
		return (tree);

	// Search the left subtree
	t_tree *left_result = find_num(tree->left, num);
	if (left_result)
		return (left_result); // If found in left, return it
	// Search the right subtree
	return find_num(tree->right, num);
}