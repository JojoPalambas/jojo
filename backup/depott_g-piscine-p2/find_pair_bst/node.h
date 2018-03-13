#ifndef NODE_H
# define NODE_H

struct bst_node
{
    int data;
    struct bst_node *left;
    struct bst_node *right;
};

int find_pair(struct bst_node *root, int k);

#endif /* !NODE_H */
