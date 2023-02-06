#include "TcpServer.hpp"

int main()
{
    boost::asio::io_context io_context;
    TcpServer server(io_context, 3333);
    io_context.run();
    return 0;
}