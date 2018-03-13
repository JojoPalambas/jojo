#ifndef COUSIN_NODES_H
# define COUSIN_NODES_H

struct bintree_node
{
    int data;
    struct bintree_node *left;
    struct bintree_node *right;
};

int is_cousin(struct bintree_node *root, struct bintree_node *a,
	      struct bintree_node *b);

#endif /* !COUSIN_NODES_H */
