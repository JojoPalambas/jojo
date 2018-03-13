#pragma once

#include <ostream>
#include <memory>

template <typename KeyType, typename ValueType>
class BST
{
public:
    BST()
    {}

    ~BST()
    {}

    const ValueType* find(const KeyType& key) const;
    ValueType* find(const KeyType& key);

    void insert(const KeyType& key, const ValueType& key);
    void insert(const ValueType& key);

    void print(std::ostream& out) const;

private:
    size_t size;
    BSTNode *root_;
};

#include "bst.hxx"
