#pragma once

#include <iostream>
#include <stdlib.h>
#include <cstdlib>

class Matrix
{
public:
    Matrix(unsigned rows, unsigned columns)
      : rows_(rows)
      , columns_(columns)
    {
        tab_ = new int*[rows_];
        for (unsigned i = 0; i < rows; i++)
            tab_[i] = new int[columns_];
    }

    ~Matrix()
    {
        for (unsigned i = 0; i < rows_; i++)
            delete tab_[i];
        delete tab_;
    }

    void fill(int val);
    void print() const;
    bool is_square() const;
    int trace() const;
    Matrix transpose() const;
    void value_set(unsigned row, unsigned column, int val);
    int value_get(unsigned row, unsigned column) const;
    unsigned rows_get() const;
    unsigned columns_get() const;

private:
    unsigned rows_;
    unsigned columns_;
    int** tab_;
};
