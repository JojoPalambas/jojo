#include "matrix.hh"

Matrix::Matrix(unsigned rows, unsigned columns)
{
    this->rows_ = rows;
    this->columns_ = columns;
    /*this->tab_ = calloc(rows, sizeof (int*));*/
    this->tab_ = new int*[rows];
    if (!this->tab_)
    {
        std::cerr << "Invalid matrix" << std::endl;
        exit(3);
    }
    for (unsigned i = 0; i < rows; i++)
    {
        /*this->tab_[i] = calloc(columns, sizeof(int));*/
        this->tab_[i] = new int[columns];
        if (!this->tab_[i])
        {
            std::cerr << "Error: invalid matrix" << std::endl;
            exit(3);
        }
    }
}

Matrix::~Matrix()
{
    for (unsigned i = 0; i < this->rows_; i++)
    {
        delete[] this->tab_[i];
    }
    delete[] this->tab_;
}

void Matrix::fill(int val)
{
    for (unsigned i = 0; i < this->rows_; i++)
    {
        for (unsigned j = 0; j < this->columns_; j++)
        {
            this->tab_[i][j] = val;
        }
    }
}

void Matrix::print() const
{
    for (unsigned i = 0; i < this->rows_; i++)
    {
        for (unsigned j = 0; j < this->columns_; j++)
        {
            std::cout << this->tab_[i][j];
            if (i == this->rows_ - 1 && j == this->columns_ - 1)
                std::cout << std::endl;
            else if (j == this->columns_ - 1)
                std::cout << '\n';
            else
                std::cout << ' ';
        }
    }
}

bool Matrix::is_square() const
{
    return (this->rows_ == this->columns_);
}

int Matrix::trace() const
{
    if (!this->is_square())
    {
        std::cerr << "Error: invalid matrix" << std::endl;
        exit(3);
    }

    int ret = 0;
    for (unsigned i = 0; i < this->rows_; i++)
    {
        ret += this->tab_[i][i];
    }

    return ret;
}

Matrix Matrix::transpose() const
{
    Matrix M(this->columns_, this->rows_);

    for (unsigned i = 0; i < this->rows_; i++)
    {
        for (unsigned j = 0; j < this->columns_; j++)
        {
            M.tab_[j][i] = this->tab_[i][j];
        }
    }
    return M;
}

void Matrix::value_set(unsigned row, unsigned column, int val)
{
    if (row >= this->rows_)
    {
        std::cout << "Error: invalid argument " << row << std::endl;
        exit(2);
    }
    if (column >= this->columns_)
    {
        std::cout << "Error: invalid argument " << column << std::endl;
        exit(2);
    }
    this->tab_[row][column] = val;

}

int Matrix::value_get(unsigned row, unsigned column) const
{
    if (row >= this->rows_)
    {
        std::cout << "Error: invalid argument " << row << std::endl;
        exit(2);
    }
    if (column >= this->columns_)
    {
        std::cout << "Error: invalid argument " << column << std::endl;
        exit(2);
    }
    return this->tab_[row][column];
}

unsigned Matrix::rows_get() const
{
    return this->rows_;
}

unsigned Matrix::columns_get() const
{
    return this->columns_;
}
