#pragma once

#include "bignum.hh"

namespace bistro
{
    template <typename T>
    BigNum<T>::BigNum(size_t base)
    {
        base_ = base;
        positive_ = true;
        digits_ = std::vector<T>();
    }

    template <typename T>
    template <typename Base>
    BigNum<T>::BigNum(std::istream& in, const Base& b)
    {
        base_ = b.get_base_num();
        positive_ = true;
        digits_ = std::vector<T>();

        auto cur = in.get();
        if (b.is_operator(cur))
        {
            in.putback(cur);
            throw std::length_error("Number starts with an operator");
        }

        while (cur && !b.is_operator(cur))
        {
            digits_.pushback(cur);
            cur = in.get();
        }
        if (cur)
            in.putback(cur);
    }

    template <typename T>
    template <typename Base>
    std::ostream& BigNum<T>::print(std::ostream& out, const Base& b) const
    {
        if (!digits_.size())
        {
            out << '0';
            return out;
        }

        if (!positive_)
            out << '-';

        if (b.get_base_num() != base_)
            throw std::invalid_argument("Wrong base number");

        for (int i = digits_.size() - 1; i >= 0; i--)
            out << b.get_digit_representation(digits_[i]);
        return out;
    }

    template <typename T>
    BigNum<T> BigNum<T>::clone() const
    {
        BigNum<T> ret = BigNum(base_);
        for (auto i: digits_)
            ret.digits_.pushback(*i);
        ret.positive_ = positive_;
    }

    template <typename T>
    typename BigNum<T>::index_t BigNum<T>::get_num_digits() const
    {
        return digits_.size();
    }

    template <typename T>
    typename BigNum<T>::digit_t BigNum<T>::get_digit(index_t i) const
    {
        if (i < 0 || i >= digits_.size())
            throw std::out_of_range("Searched for digit out of range");

        return digits_[i];
    }

    template <typename T>
    void BigNum<T>::set_digit(index_t i, digit_t d)
    {
        if (i < 0)
            throw std::out_of_range("Tried to change value of negative index");
        if (i >= digits_.size())
        {
            for (size_t inc = digits_.size(); inc <= i; inc++)
                digits_.push_back(0);
        }

        digits_[i] = d;
    }

    template <typename T>
    bool BigNum<T>::is_positive() const
    {
        return positive_;
    }

    template <typename T>
    void BigNum<T>::set_positive(bool p)
    {
        positive_ = p;
    }

    template <typename T>
    bool BigNum<T>::operator>(const self_t& other) const
    {
        if (digits_.size() > other.digits_.size())
            return true;
        if (digits_.size() < other.digits_.size())
            return false;

        auto i = digits_.end();
        auto j = other.digits_.end();
        while (i != digits_.begin() && j != other.digits_.begin())
        {
            if (*i > *j)
                return true;
            if (*i < *j)
                return false;
            i--;
            j--;
        }
        return false;
    }

    template <typename T>
    bool BigNum<T>::operator==(const self_t& other) const
    {
        if (digits_.size() != other.digits_.size())
            return false;

        auto i = digits_.end();
        auto j = other.digits_.end();
        while (i != digits_.begin() && j != other.digits_.begin())
        {
            if (*i != *j)
                return false;
            i--;
            j--;
        }
        return true;
    }

    template <typename T>
    BigNum<T>::operator bool() const
    {
        return digits_.size() != 0;
    }
}
