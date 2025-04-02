Assignment name  : search_binary_tree
Expected files   : search_binary_tree.c
Allowed functions: none
--------------------------------------------------------------------------------

Implement a function that searches for a given value in a binary search tree.
The function should return 1 if the value is found in the tree, otherwise it hsould return 0.

The function should be declared as follows:
int search_binary_tree(t_btree *root, int value);

You have to #include (but not add to git) a ft_btree.h file, which is only available on the server during grading,
that will only contain:

typedef struct s_btree
{
  int value;
  struct s_btree *left;
  struct s_btree *right;
} t_btree;

The tree will not be ordered in any specific way.
