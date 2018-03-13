#ifndef MIRROR_BINTREE_H
# define MIRROR_BINTREE_H

struct bintree_node
{
    int data;
    struct bintree_node *left;
    struct bintree_node *right;
};

void mirror(struct bintree_node *root);

#endif /* !MIRROR_BINTREE_H */
