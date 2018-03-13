#include <iostream>
#include <csignal>

void sigint_handler(int signal)
{
    if (signal == SIGINT)
    {
        std::cout << "Program closed by SIGINT" << std::endl;
        exit(1);
    }
    else
        std::cout << "Unhandled signal" << std::endl;
}

int main()
{
    std::signal(SIGINT, sigint_handler);
    while (true)
    {
        std::cout << "Infinite loop" << std::endl;
    }
}
