#pragma once

#include <ostream>
#include <memory>

template <typename KeyType, typename ValueType>
class BSTNode
{
public:
    BSTNode(KeyType key, ValueType value)
      : empty_(false)
      , key_(key)
      , value_(value)
      , left_(nullptr)
      , right_(nullptr)
    {}

    ~BSTNode()
    {
        delete left_;
        delete right_;
    }

    const ValueType* find(const KeyType& key) const;
    ValueType* find(const KeyType& key);

    void insert(const KeyType& key, const ValueType& value);
    void remove(const KeyType& key);

    void print(std::ostream& out) const;

private:
    bool empty_;

    KeyType key_;
    ValueType value_;

    BSTNode *left_;
    BSTNode *right_;
};

#include "bst_node.hxx"
