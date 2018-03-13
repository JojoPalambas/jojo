#pragma once

#include <iostream>

template <typename T>
class Stack
{
public:
    Stack(unsigned max_size)
      : max_size_(max_size)
    {
        tab_ = new T[max_size_];
    }

    ~Stack()
    {
        //delete tab_;
    }

    bool empty() const;
    unsigned size() const;
    T& peek();
    const T& peek() const;
    bool push(const T& elt);
    void pop();

private:
    unsigned max_size_;
    unsigned size_;
    T *tab_;
};

#include "stack.hxx"
