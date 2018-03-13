#include <iostream>

#include "person.hh"

int main()
{
    Person my_person("Meliodas", 19);

    const Person& my_person2 = my_person;

    std::cout << "name: "    << my_person2.name_get()
              << ", years: " << my_person2.age_get() << std::endl;

    std::string name = "Elisabeth";
    my_person.name_set(name);
    my_person.age_set(52);

    std::cout << "name: "    << my_person2.name_get()
              << ", years: " << my_person2.age_get() << std::endl;
}
