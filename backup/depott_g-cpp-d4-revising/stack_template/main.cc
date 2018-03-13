#include <iostream>
#include "stack.hh"

int main()
{
  Stack<std::string> strings(5);
  Stack<int> ints(5);

  if (strings.empty())
    std::cout << "No string" << std::endl;
  if (ints.empty())
    std::cout << "No int" << std::endl;

  strings.push("first");
  strings.push("second");
  std::cout << "There are " << strings.size() << " strings" << std::endl;
  ints.push(1);
  std::cout << "There are " << ints.size() << " ints" << std::endl;

  std::cout << "The last string is " << strings.peek() << std::endl;
  std::cout << "The last int is " << ints.peek() << std::endl;

  strings.pop();
  ints.pop();
  if (!strings.empty())
    std::cout << "Still one string" << std::endl;
  if (ints.empty())
    std::cout << "No int" << std::endl;
}
