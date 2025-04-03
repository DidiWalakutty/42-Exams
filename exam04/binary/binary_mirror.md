Assignment name  : binary_mirror
Expected files   : binary_mirror.c
Allowed functions: malloc, free
--------------------------------------------------------------------------------

Implement a function that returns the mirror of a binary tree.
A binary tree is a tree where all nodes have at most 2 childrene. a left one and a right one.

The function should be declared as follows:
t_btree* mirror_binary_tree(const t_btree *root);

Use the t_btree.h file that only includes:

typedef struct s_btree
{
  int value;
  struct s_btree *left;
  struct s_btree *right;
} t_btree;

If root is NULL, return NULL.

Example 1
      1
     /  \
    2   3
   / \   / \
   4  5  6 7

Expected outcome:
      1
     /  \
    3   2
   / \   / \
  7  6   5  4

example 2:
      50
     /  \
  18  83
   / \   
3    28
       \
        32
Expected outcome:
      50
     /  \
    83  18
        / \   
       28  3
       / 
      32