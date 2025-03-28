#include <stdlib.h>
#include "ft_btree.h"

// Inserts a new value into a BST
// Recursively finds the correct spot and insert a new node.
t_btree* insert_binary_tree(t_btree *root, int value)
{
	if (!root)
	{
		root = malloc(sizeof(t_btree));
		if (!root)
			return (NULL);
		root->value = value;
		root->left = NULL;
		root->right = NULL;
	}
	else if (value < root->value)
		root->left = insert_binary_tree(root->left, value);
	else if (value > root->value)
		root->right = insert_binary_tree(root->right, value);
	return (root);
}