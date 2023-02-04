/*
** EPITECH PROJECT, 2023
** Server
** File description:
** Server
*/

#ifndef UDPSERVER_HPP_
    #define UDPSERVER_HPP_

    #include <ctime>
    #include <iostream>
    #include <string>
    #include <boost/array.hpp>
    #include <boost/bind/bind.hpp>
    #include <boost/shared_ptr.hpp>
    #include <boost/asio.hpp>

    using namespace boost::asio;
    using namespace boost::asio::ip;

    class UdpServer
    {
        private:
            udp::socket _socker;
            udp::endpoint _remote_endpoint;
            boost::array<char, 30> _buffer;
            void handler_received(const boost::system::error_code &error,
                            std::size_t /*bytes_transferred*/);
            void handler_send(boost::shared_ptr<std::string> /*message*/,
                        const boost::system::error_code & /*error*/,
                        std::size_t /*bytes_transferred*/);

        public:
            UdpServer(boost::asio::io_service &io_service, int port);
            void start_receive();
            void send_data();
            ~UdpServer();
    };

#endif /* !UDPSERVER_HPP_ */
