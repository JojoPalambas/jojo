#include "computer.hh"

std::ostream& operator<<(std::ostream& ostr, const Computer& c)
{
    ostr << "Brand: " << c.get_brand() << ", Name: " << c.get_name()
         << ", Power: " << c.get_power();
    return ostr;
}

const std::string& Computer::get_brand() const
{
    return brand_;
}

const std::string& Computer::get_name() const
{
    return name_;
}

int Computer::get_power() const
{
    return power_;
}

bool Computer::operator==(const Computer& c) const
{
    return ((!brand_.compare(c.brand_)) && (!name_.compare(c.name_))
            && (power_ == c.power_));
}

bool Computer::operator!=(const Computer& c) const
{
    return !(*this == c);
}

bool Computer::operator<(const Computer& c) const
{
    if (brand_.compare(c.brand_) < 0)
        return true;
    if (brand_.compare(c.brand_) > 0)
        return false;
    if (name_.compare(c.name_) < 0)
        return true;
    if (name_.compare(c.name_) > 0)
        return false;
    if (power_ < c.power_)
        return true;
    if (power_ > c.power_)
        return false;
    return false;
}

bool Computer::operator>(const Computer& c) const
{
    if (brand_.compare(c.brand_) < 0)
        return false;
    if (brand_.compare(c.brand_) > 0)
        return true;
    if (name_.compare(c.name_) < 0)
        return false;
    if (name_.compare(c.name_) > 0)
        return true;
    if (power_ < c.power_)
        return false;
    if (power_ > c.power_)
        return true;
    return false;
}

bool Computer::operator<=(const Computer& c) const
{
    if (brand_.compare(c.brand_) < 0)
        return true;
    if (brand_.compare(c.brand_) > 0)
        return false;
    if (name_.compare(c.name_) < 0)
        return true;
    if (name_.compare(c.name_) > 0)
        return false;
    if (power_ < c.power_)
        return true;
    if (power_ > c.power_)
        return false;
    return true;
}

bool Computer::operator>=(const Computer& c) const
{
    if (brand_.compare(c.brand_) < 0)
        return false;
    if (brand_.compare(c.brand_) > 0)
        return true;
    if (name_.compare(c.name_) < 0)
        return false;
    if (name_.compare(c.name_) > 0)
        return true;
    if (power_ < c.power_)
        return false;
    if (power_ > c.power_)
        return true;
    return true;
}
