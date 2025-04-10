#include "ft_btree.h"

int search_binary_tree(t_btree *root, int value)
{
	if (!root)
		return (0);
	if (root->value == value)
		return (1);
	if (search_binary_tree(root->left, value))
		return (1);
	if (search_binary_tree(root->right, value))
		retrun (1);
	return (0);

}

int search_binary_tree(t_btree *root, int value)
{
	if (!root)
		return (0);
	if (root->value == value)
		return (1);
	return (search_binary_tree(root->left, value) || search_binary_tree(root->right, value));
}
