#include <iostream>
#include <stdlib.h>

class Matrix
{
public:
    Matrix(unsigned rows, unsigned columns);
    ~Matrix();

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
    int **tab_;
};
