#include "../src/base.hh"
#include "../src/bignum.hh"

#include <sstream>

void tag(std::string s)
{
    std::cout << "----- " << s << std::endl;
}

int compare(bistro::BigNum<uint8_t>& bn, bistro::Base<uint8_t, char>& b,
            std::string str)
{
    auto io = std::stringstream();
    try
    {
        bn.print(io, b);
    }
    catch (int i)
    {
        std::cout << "Exception encountered: " << i << std::endl;
        return 0;
    }
    std::string comparator;
    io >> comparator;
    return (!str.compare(comparator)) + 1;
}

void test(bistro::BigNum<uint8_t>& bn, bistro::Base<uint8_t, char>& b,
          std::string str)
{
    int ans = compare(bn, b, str);
    if (!ans)
        std::cout << "========== [HS] ==========\n" << "-> Execution stopped\n";
    else if(ans == 1)
    {
        std::cout << "========== [KO] ==========\n"
                  << "-> Comparison failed:\n-> BigNum = ";
        bn.print(std::cout, b);
        std::cout << " ; Target = " << str << std::endl;
    }
    else
    {
        std::cout << "========== [OK] ==========\n"
                  << "-> Comparison succeeded:\n-> BigNum = " << str
                  << " ; Target = " << str << std::endl;
    }
    std::cout << "\n" << std::endl;
}

int main()
{
    std::cout << std::endl;

    bistro::BigNum<uint8_t> bn = bistro::BigNum<uint8_t>(10);
    bistro::Base<uint8_t, char> b = bistro::Base<uint8_t, char>();

    tag("Empty number:");
    test(bn, b, "0");

    bn.set_digit(0, 3);
    bn.set_digit(1, 2);
    bn.set_digit(2, 1);

    tag("Number 123:");
    test(bn, b, "123");

    bn.set_positive(true);

    tag("Number +123:");
    test(bn, b, "123");

    bn.set_positive(false);

    tag("Number -123:");
    test(bn, b, "-123");

    bn.set_digit(0, 1);
    bn.set_digit(1, 0);
    bn.set_digit(2, 0);

    tag("Number 001:");
    test(bn, b, "-1");
}
