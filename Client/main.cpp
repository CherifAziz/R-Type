// /*
// ** EPITECH PROJECT, 2023
// ** main
// ** File description:
// ** main
// */

// #include <string>

// #include "Core.hpp"

// #include <boost/asio.hpp>
// #include <boost/bind.hpp>
// #include <boost/date_time/posix_time/posix_time.hpp>
// #include <iostream>

// static bool check_parameter_is_helper(std::string param)
// {
//     if (param == "-h" || param == "--help" || param == "-help")
//         return true;
//     return false;
// }

// static void display_help()
// {
//     std::cout << "RTYPE" << std::endl;
//     std::cout << "USAGE" << std::endl;
//     std::cout << "\t./rtype [ip] [port]" << std::endl;
//     std::cout << std::endl;
// }

// static int start_rtype(std::string ip, std::string port)
// {
//     try {
//         boost::asio::io_context ioc;
//         rtype::Core core(ioc, ip, port);

//         core.loopGame();
//         ioc.run();
//     } catch (const std::exception& e) {
//         std::cout << "ERROR: " << e.what() << std::endl;
//         return 84;
//     }
//     return 0;
// }

// int main(int ac, char **av)
// {
//     if (ac == 2 && check_parameter_is_helper((std::string)av[1])) {
//         display_help();
//         return (0);
//     } else if (ac == 3)
//         return start_rtype((std::string) av[1], (std::string) av[2]);
//     return 84;
// }
#include <stdio.h>
#include <chrono>

int main () {
    double sum = 0;
    double add = 1;

    // Start measuring time
    auto begin = std::chrono::high_resolution_clock::now();
    
    int iterations = 1000*1000*1000;
    for (int i=0; i<iterations; i++) {
        sum += add;
        add /= 2.0;
    }
    
    // Stop measuring time and calculate the elapsed time
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    
    printf("Result: %.20f\n", sum);
    
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    
    return 0;
}