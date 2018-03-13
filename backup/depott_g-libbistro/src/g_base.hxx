#pragma once

#include "base.hh"
namespace bistro
{
    template <typename Value, typename Char>
        Base<Value, Char>::Base()
        {
            digits_ = std::vector<char_t>();

            auto l = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
            for (auto i : l)
                digits_.push_back(i);
        }

    template <typename Value, typename Char>
        Base<Value, Char>::Base(std::initializer_list<char_t> list)
        {
            digits_ = std::vector<char_t>();
            for (auto i : list)
                digits_.push_back(*i);
        }

    template <typename Value, typename Char>
        size_t Base<Value, Char>::get_base_num() const
        {
            return digits_.size();
        }

    template <typename Value, typename Char>
        void Base<Value, Char>::add_digit(char_t repr)
        {
            for (auto i : digits_)
                if (*i == repr)
                    throw std::invalid_argument("Digit doubled in the base");
            if (is_operator(repr))
                throw std::invalid_argument("Digit is a reserved operator");

            digits_.push_back(repr);
        }

    template <typename Value, typename Char>
        bool Base<Value, Char>::is_operator(char_t c)
        {
            auto forbidden = { '+', '-', '*', '/', '=', '%', '(', ')' };
            for (auto i : forbidden)
                if (i == c)
                    return true;
            return false;
        }

    template <typename Value, typename Char>
        Char Base<Value, Char>::get_digit_representation(value_t i) const
        {
            if (i < 0 || i >= digits_.size())
                throw std::out_of_range("Digit wanted out of the base bounds");
            return digits_[i];
        }

    template <typename Value, typename Char>
        Value Base<Value, Char>::get_char_value(char_t r) const
        {
            for (auto i : digits_)
                if (*i == r)
                    return i - digits_.begin();
            throw std::out_of_range("Digit doesn't exist in the base");
        }
}
