#include <iostream>
#include "UdpServer.hpp"

int main()
{
  std::string msg;
  boost::asio::io_service io;
  UdpServer udpserver(io, 3333);
  io.run();

  // while (1) {
  //   std::cin >> msg;

  //   if (msg == "quit")
  //     break;
  //   else
  //     udpserver.send_data()
  // }
}