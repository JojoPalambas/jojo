#pragma once

#include "shop.hh"

class Computer
{
public:
    Computer(const std::string& brand,
            const std::string& name,
            int power)
        : brand_(brand)
        , name_(name)
        , power_(power)
    {}

    ~Computer()
    {}

    const std::string& get_brand() const;
    const std::string& get_name() const;
    int get_power() const;

    bool operator==(const Computer& c) const;
    bool operator!=(const Computer& c) const;
    bool operator<(const Computer& c) const;
    bool operator>(const Computer& c) const;
    bool operator<=(const Computer& c) const;
    bool operator>=(const Computer& c) const;

private:
    std::string brand_;
    std::string name_;
    int power_;
};

std::ostream& operator<<(std::ostream& ostr, const Computer& c);
