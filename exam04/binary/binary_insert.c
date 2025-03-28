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
	 else if (root->value > value)  // If root's value is greater than the new value, insert in the left subtree
        root->left = insert_binary_tree(root->left, value);
    else if (root->value < value)  // If root's value is smaller than the new value, insert in the right subtree
        root->right = insert_binary_tree(root->right, value);
  	// If root->value == value, we do nothing (duplicate values are ignored
	return (root);
}