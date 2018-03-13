#include <iostream>

#include "thread_pool.hh"

void func()
{
    for (int i = 0; i < 10; i++)
        std::cout << i;
    std::cout << "end" << std::endl;
}

int main()
{
    ThreadPool TP(10);
    for (int i = 0; i < 15; i++)
        TP.add_func(func);
}
