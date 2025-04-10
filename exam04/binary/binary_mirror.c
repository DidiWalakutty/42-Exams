#include "ft_btree.h"
#include <stdlib.h>

#include "ft_btree.h"
#include <stdio.h>

t_btree	*new_node(int value)
{
	t_btree	*new = malloc(sizeof(t_btree));
	if (!new)
		return (NULL);
	new->value = value;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_btree	*create_tree()
{
	t_btree	*root = new_node(1);
	root->left = new_node(2);
	root->right = new_node(3);
	
	root->left->left = new_node(4);
	root->left->right = new_node(5);

	root->right->left = new_node(6);
	root->right->right = new_node(7);
	return (root);
}

void	print_tree(t_btree *root, int spaces)
{
	if (!root)
		return ;

	spaces += 5;
	print_tree(root->right, spaces);
	printf("\n");
	for (int i = 5; i < spaces; i++)
		printf(" ");
	printf("%d\n", root->value);

	print_tree(root->left, spaces);
}

t_btree *mirror_binary_tree(const t_btree *root)
{
	if (!root)
		return NULL;

	t_btree *new_node = malloc(sizeof(t_btree));
	if (!new_node)
		return NULL;

	new_node->value = root->value;
	new_node->left = mirror_binary_tree(root->right);
	new_node->right = mirror_binary_tree(root->left);

	return new_node;
}

int	main()
{
	t_btree *root = create_tree();
	printf("Original tree:\n");
	print_tree(root, 0);

	printf("mirror binary tree:\n");
	root = mirror_binary_tree(root);
	printf("\nMirrored tree:\n");
	print_tree(root, 0);
}
