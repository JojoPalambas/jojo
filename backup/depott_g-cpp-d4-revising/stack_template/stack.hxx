#pragma once

#include "stack.hh"

template <typename T>
bool Stack<T>::empty() const
{
    return !size_;
}

template <typename T>
unsigned Stack<T>::size() const
{
    return size_;
}

template <typename T>
T& Stack<T>::peek()
{
    return tab_[size_ - 1];
}

template <typename T>
const T& Stack<T>::peek() const
{
    return tab_[size_ - 1];
}

template <typename T>
bool Stack<T>::push(const T& elt)
{
    if (size_ >= max_size_)
        return false;
    tab_[size_] = elt;
    size_++;
    return true;
}

template <typename T>
void Stack<T>::pop()
{
    if (size_ <= 0)
        return;
    size_--;
}

template <typename T>
std::ostream& operator<<(std::ostream ostr, const Stack<T>& s)
{
    for (unsigned i = 0; i < s.size_; i++)
    {
        ostr << s.tab_[i];
        if (i < s.size_ - 1)
            ostr << ' ';
    }
    return ostr;
}
