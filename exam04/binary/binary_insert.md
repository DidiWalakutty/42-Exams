Assignment name  : binary_insert
Expected files   : binary_insert.c
Allowed functions: malloc
--------------------------------------------------------------------------------

Implement a function that inserts a new node with a given value into a binary
search tree.

The function should return a pointer to the root node of the modified
binary search tree.

The function is declared as follow:
t_btree* insert_binary_tree(t_btree *root, int value);

You have to use the ft_btree.h file that includes:

typedef struct s_btree
{
	int value;
	struct s_btree *left;
	struct s_btree *right;
}	t_btree;

If the root is NULL, return the new node as root.
Duplicate values should be ignored.

Values bigger than the root should be inserted in the right subtree.
Values smaller than the root should be inserted in the left subtree.

Values will always be inserted at the END of a subtree.