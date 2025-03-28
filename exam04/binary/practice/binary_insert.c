#include "ft_btree.h"
#include <stdlib.h>

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
	else if (root->value > value)
		root->left = insert_binary_tree(root->left, value);
	else if (root->value < value)
		root->right = insert_binary_tree(root->right, value);
	return (root);
}