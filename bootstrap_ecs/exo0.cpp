/*
** EPITECH PROJECT, 2023
** cpp
** File description:
** test
*/

#include <iostream>

class entity {
    std::size_t _value;
    public:
        explicit entity(std::size_t value) : _value(value) {}
        operator size_t() const { return _value; }
};

void print_size(entity exp)
{
    std::cout << exp + 5 << std::endl;
}

int main(int ac, char **av)
{
    print_size(entity(20));
}