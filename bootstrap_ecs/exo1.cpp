/*
** EPITECH PROJECT, 2023
** cpp
** File description:
** exo1
*/

#include <iostream>

#include "ComponentMap.h"

class TestComponent
{
    public:
        TestComponent(std::string value) : _value(value) {};
        void display()
        {
            std::cout << _value << std::endl;
        }
        bool operator==(TestComponent const &other) const { return _value == other._value; };
    private:
        std::string _value;
};

int main(int ac, char **av)
{
    ComponentMap<TestComponent> test;
    TestComponent first("1");
    TestComponent second("2");
    TestComponent third("3");

    test.put(first);
    test.put(second);
    test.put(third);
    test.display();
    TestComponent value = test.get(2);
    value.display();
    test.display();
    std::cout << test.get_index(value) << std::endl;
    test.pop(2);
    test.display();
    return 0;
}