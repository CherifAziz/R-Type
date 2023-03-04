/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include <string>

#include "Core.hpp"

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>

static bool check_parameter_is_helper(std::string param)
{
    if (param == "-h" || param == "--help" || param == "-help")
        return true;
    return false;
}

static void display_help()
{
    std::cout << "RTYPE" << std::endl;
    std::cout << "USAGE" << std::endl;
    std::cout << "\t./r-type_server [port]" << std::endl;
    std::cout << std::endl;
}

static int start_rtype(std::string port)
{
    try {
        boost::asio::io_context ioc;
        rtype::Core core(ioc, "", port);

        core.loopGame();
        ioc.run();
    } catch (const std::exception& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
        return 84;
    }
    return 0;
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 84;
    if (check_parameter_is_helper((std::string)av[1]))
        display_help();
    else
        return start_rtype((std::string) av[1]);
    return 0;
}