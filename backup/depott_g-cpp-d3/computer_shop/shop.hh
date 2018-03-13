#pragma once

#include <algorithm>
#include <iostream>
#include <string>

#include <vector>

template <class T>
class Shop
{
public:
    Shop()
        : vect_(std::vector<T>{})
    {}

    ~Shop()
    {}

    void inventory(std::ostream& ostr) const;
    void add_product(const T& product);
    bool remove_product(size_t pos);
    const T& get_product(size_t pos) const;
    bool has_product(const T& product) const;
    void sort();

private:
    std::vector<T> vect_;
};

#include "shop.hxx"
