#pragma once

#include "shop.hh"

template <class T>
void Shop<T>::inventory(std::ostream& ostr) const
{
    for (auto &it : vect_)
        ostr << it << '\n';
}

template <class T>
void Shop<T>::add_product(const T& product)
{
    vect_.push_back(product);
}

template <class T>
bool Shop<T>::remove_product(size_t pos)
{
    if (pos > vect_.size() || pos < 1)
        return false;
    vect_.erase(vect_.begin() + pos - 1);
    return true;
}

template <class T>
const T& Shop<T>::get_product(size_t pos) const
{
    return vect_.at(pos - 1);
}

template <class T>
bool Shop<T>::has_product(const T& product) const
{
    for (size_t i = 0; i < vect_.size(); i++)
        if (vect_.at(i) == product)
            return true;
    return false;
}

template <class T>
void Shop<T>::sort()
{
    /*vect_.sort(vect_.begin(), vect_.end());
    vect_.reverse(vect_.begin(), vect_.end());*/

    std::sort(vect_.begin(), vect_.end());
    std::reverse(vect_.begin(), vect_.end());
}
