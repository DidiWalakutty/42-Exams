#include "ft_btree.h"

int search_binary_tree(t_btree *root, int value)
{
    if (!root) // Base case: empty tree or leaf reached
        return 0;
    if (root->value == value) // Found the value
        return 1;
    
    // Search both left and right subtrees
    return search_binary_tree(root->left, value) || search_binary_tree(root->right, value);
}

// Use either one


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
 