#include <stdlib.h>
#include "ft_btree.h"

t_btree* insert_binary_tree(t_btree *root, int value)
{
	if (!root)
	{
		root = malloc(sizeof(t_btree));
		root->value = value;
		root->left = NULL;
		root->right = NULL;
	}
	else if (value < root->value)
		root->left = insert_binary_tree(root->left, value);
	else
		root->right = insert_binary_tree(root->right, value);
	return (root);
}