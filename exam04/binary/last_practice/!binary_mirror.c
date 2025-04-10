#include "ft_btree.h"
#include <stdlib.h>

t_btree *mirror_binary_tree(const t_btree *root)
{
	if (!root)
		return (NULL);
	t_btree *new = malloc(sizeof(t_btree));
	if (!new)
		return (NULL);
	new->value = root->value;
	new->left = mirror_binary_tree(root->right);
	new->right = mirror_binary_tree(root->left);
	return (new);
}