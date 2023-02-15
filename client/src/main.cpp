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

void print(const boost::system::error_code&, boost::asio::deadline_timer* t,int* count)
{
    if (*count < 5)
    {
        std::cout << *count << std::endl;
        ++(*count);
        t->expires_from_now(boost::posix_time::seconds(1));
        t->async_wait(boost::bind(print, boost::asio::placeholders::error, t, count));
    }
}

int main(int ac, char **av)
{
    boost::asio::io_service io;
    int count = 0;
    boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));

    t.async_wait(boost::bind(print, boost::asio::placeholders::error, &t, &count));

    io.run();
    std::cout << "Final count is " << count << std::endl;

    return 0;
    // if (ac == 2 && check_parameter_is_helper((std::string)av[1]))
    //     display_help();
    // else
    //     return start_rtype();
    return 0;
}