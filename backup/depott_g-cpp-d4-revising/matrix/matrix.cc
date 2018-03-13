#include "matrix.hh"

void Matrix::fill(int val)
{
    for (unsigned i = 0; i < rows_; i++)
        for (unsigned j = 0; j < columns_; j++)
            tab_[i][j] = val;
}

void Matrix::print() const
{
    for (unsigned i = 0; i < rows_; i++)
    {
        for (unsigned j = 0; j < columns_; j++)
        {
            std::cout << tab_[i][j];
            if (j == columns_ - 1)
                std::cout << std::endl;
            else
                std::cout << ' ';
        }
    }
}

bool Matrix::is_square() const
{
    return rows_ == columns_;
}

int Matrix::trace() const
{
    if (!this->is_square())
    {
        std::cout << "Error: invalid matrix" << std::endl;
        exit(3);
    }
    int x = 0;
    for (unsigned i = 0; i < rows_; i++)
        x += tab_[i][i];
    return x;
}

Matrix Matrix::transpose() const
{
    Matrix ret = Matrix(columns_, rows_);
    for (unsigned i = 0; i < rows_; i++)
        for (unsigned j = 0; j < columns_; j++)
            ret.tab_[j][i] = tab_[i][j];
    return ret;
}

void Matrix::value_set(unsigned row, unsigned column, int val)
{
    if (row >= rows_)
    {
        std::cout << "Error: invalid argument " << row << std::endl;
        exit(2);
    }

    if (column >= columns_)
    {
        std::cout << "Error: invalid argument " << column << std::endl;
        exit(2);
    }
    tab_[row][column] = val;
}

int Matrix::value_get(unsigned row, unsigned column) const
{
    if (row >= rows_)
    {
        std::cout << "Error: invalid argument " << row << std::endl;
        exit(2);
    }

    if (column >= columns_)
    {
        std::cout << "Error: invalid argument " << column << std::endl;
        exit(2);
    }
    return tab_[row][column];
}

unsigned Matrix::rows_get() const
{
    return rows_;
}

unsigned Matrix::columns_get() const
{
    return columns_;
}
