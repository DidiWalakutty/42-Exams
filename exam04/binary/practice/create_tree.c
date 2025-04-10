#include "ft_btree.h"
#include <stdio.h>

t_btree *new_node(int value)
{
	t_btree *new = malloc(sizeof(t_btree));
	if (!new)
		return (NULL);
	new->value = value;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_btree	*create_tree()
{
	t_btree *root = new_node(1);
	root->left = new_node(5);
	root->right = new_node(10);

	root->left->left = new_node(4);
	root->left->right = new_node(8);

	root->right->left = new_node(20);
	root->right->right = new_node(40);
	return (root);
}

void	print_tree(t_btree *root, int spaces)
{
	if (!root)
		return ;
	spaces += 5;
	print_tree(root->left, spaces);
	printf("\n");
	for (int i = 5; i < spaces; i++)
		printf(" ");
	printf("%d\n", root->value);
	print_tree(root->right, spaces);
}

int	main()
{
	t_btree *root = create_tree();

	printf("Original tree:\n");
	print_tree(root, 0);
}