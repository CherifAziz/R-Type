#include <iostream>
#include <thread>
#include "Client.hpp"

int main(int argc, char *argv[])
{
    std::string msg;
    boost::asio::io_context ioc;
    Client client(ioc, std::string(argv[1]), std::atoi(argv[2]));

    std::thread thread([&ioc] { ioc.run(); });

    while (1) {
        std::cin >> msg;

        if (msg == "quit")
            break;
        else
            client.sendDataToServer("test");
    }
    return 0;
}