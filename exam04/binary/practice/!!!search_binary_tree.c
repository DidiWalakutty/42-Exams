#include "ft_btree.h"

int search_binary_tree(t_btree *root, int value)
{
	if (!root)
		return (0);
	if (root->value == value)
		return (1);
	return (search_binary_tree(root->left, value) || search_binary_tree(root->right, value));
}

int search_binary_tree(t_btree *root, int value)
{
	if (!root)
		return (0);
	if (root->value == value)
		return (1);
	
	int left = search_binary_tree(root->left, value);
	int right = search_binary_tree(root->right, value);
	return (left || right);
}