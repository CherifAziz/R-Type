/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include <string>

#include "Core.hpp"

static bool check_parameter_is_helper(std::string param)
{
    if (param == "-h" || param == "--help" || param == "-help")
        return true;
    return false;
}

static void display_help()
{
    std::cout << "RTYPE HELPER" << std::endl;
    std::cout << std::endl;
    std::cout << "Not really a lot of information right now" << std::endl;
    std::cout << "Come back later" << std::endl;
}

static int start_rtype()
{
    try {
        rtype::Core core;

        core.loopGame();
    } catch (const std::exception& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
        return 84;
    }
    return 0;
}

int main(int ac, char **av)
{
    if (ac == 2 && check_parameter_is_helper((std::string)av[1]))
        display_help();
    else
        return start_rtype();
    return 0;
}