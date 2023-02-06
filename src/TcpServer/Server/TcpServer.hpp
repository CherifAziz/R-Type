/*
** EPITECH PROJECT, 2023
** TcpServer
** File description:
** TcpServer
*/

#ifndef TCPSERVER_HPP_
    #define TCPSERVER_HPP_

    #include "ClientServer.hpp"
    #include <ctime>
    #include <iostream>
    #include <string>
    #include <boost/bind/bind.hpp>
    #include <boost/shared_ptr.hpp>
    #include <boost/enable_shared_from_this.hpp>
    #include <boost/asio.hpp>
    #include <memory>

    using boost::asio::ip::tcp;
    using namespace boost::placeholders;

    class TcpServer {
        public:
            TcpServer(boost::asio::io_context& ioc, int port);
            void start_accept();
            void handle_accept(std::shared_ptr<ClientServer> client, const boost::system::error_code& err);
            ~TcpServer();

        protected:
        private:
            tcp::acceptor _acceptor;
            boost::asio::io_context &_io_context;
            std::vector<std::shared_ptr<ClientServer> > _clients;
    };

#endif /* !TCPSERVER_HPP_ */
