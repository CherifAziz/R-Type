#include <fmt/format.h>

#include <iostream>

int main()
{
    std::cout << fmt::format("Which tool is better: {} or {}?\n",
                           "Conan",
                           "Vcpkg");
}