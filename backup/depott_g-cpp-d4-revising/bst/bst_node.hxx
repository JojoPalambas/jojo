#pragma once

#include "bst_node.hh"

template <typename KeyType, typename ValueType>
const ValueType* BSTNode<KeyType, ValueType>::find(const KeyType& key) const
{
    if (key == key_)
    {
        if (!empty_)
            return &value_;
        return nullptr;
    }
    if (key < key_)
    {
        if (left_ == nullptr)
            return nullptr;
        else
            return left_->find(key);
    }
    if (key > key_)
    {
        if (right_ == nullptr)
            return nullptr;
        else
            return right_->find(key);
    }
    return nullptr;
}

template <typename KeyType, typename ValueType>
ValueType* BSTNode<KeyType, ValueType>::find(const KeyType& key)
{
    if (key == key_)
    {
        if (!empty_)
            return &value_;
        return nullptr;
    }
    if (key < key_)
    {
        if (left_ == nullptr)
            return nullptr;
        else
            return left_->find(key);
    }
    if (key > key_)
    {
        if (right_ == nullptr)
            return nullptr;
        else
            return right_->find(key);
    }
    return nullptr;
}

template <typename KeyType, typename ValueType>
void BSTNode<KeyType, ValueType>::insert(const KeyType& key,
                                         const ValueType& value)
{
    if (key < key_)
    {
        if (left_ == nullptr)
            left_ = new BSTNode<KeyType, ValueType>(key, value);
        else
            left_->insert(key, value);
        return;
    }
    if (key > key_)
    {
        if (right_ == nullptr)
            right_ = new BSTNode<KeyType, ValueType>(key, value);
        else
            right_->insert(key, value);
        return;
    }
    value_ = value;
    empty_ = false;
}

template <typename KeyType, typename ValueType>
void BSTNode<KeyType, ValueType>::remove(const KeyType& key)
{
    if (key == key_)
    {
        empty_ = true;
        return;
    }
    if (key < key_)
    {
        if (left_ == nullptr)
            return;
        else
            left_->remove(key);
        return;
    }
    if (key > key_)
    {
        if (right_ == nullptr)
            return;
        else
            right_->remove(key);
        return;
    }
}

template <typename KeyType, typename ValueType>
void BSTNode<KeyType, ValueType>::print(std::ostream& out) const
{
    if (left_ != nullptr)
        left_->print(out);
    if  (!empty_)
        out << key_ << ": " << value_ << "\n";
    if (right_ != nullptr)
        right_->print(out);
}
