#include <iostream>

#include "bst_node.hh"

int main()
{
    BSTNode<int, std::string> a = BSTNode<int, std::string>(5, "tartare");
    a.insert(6, "tuture");
    a.insert(3, "c");
    a.insert(2, "b");
    a.insert(4, "totor");
    a.insert(26, "q");
    a.insert(1, "a");
    a.insert(25, "y");
    a.insert(26, "z");
    a.print(std::cout);

    a.remove(2);
    a.remove(5);
    a.remove(25);
    a.remove(1000);
    a.print(std::cout);

    a.insert(5, "I'm back");
    a.print(std::cout);

    std::string *found;
    found = a.find(1);
    if (found != nullptr)
        std::cout << *found << ' ';
    found = a.find(5);
    if (found != nullptr) 
        std::cout << *found << ' ';
    found = a.find(25);
    if (found != nullptr)
        std::cout << *found << ' ';
    found = a.find(1000);
    if (found != nullptr)
        std::cout << *found << ' ';
    found = a.find(26);
    if (found != nullptr)
        std::cout << *found << ' ' << std::endl;
}
