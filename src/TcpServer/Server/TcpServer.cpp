/*
** EPITECH PROJECT, 2023
** TcpServer
** File description:
** TcpServer
*/

#include "TcpServer.hpp"

TcpServer::TcpServer(boost::asio::io_context& ioc, int port): _acceptor(ioc, tcp::endpoint(tcp::v4(), port)), _io_context(ioc)
{
    this->start_accept();
}

TcpServer::~TcpServer()
{
}

void TcpServer::start_accept()
{
    this->_clients.push_back(std::make_shared<ClientServer>(this->_io_context));
    this->_acceptor.async_accept(this->_clients[this->_clients.size() - 1]->getSocket(),
            boost::bind(&TcpServer::handle_accept, this, this->_clients[this->_clients.size() - 1], boost::asio::placeholders::error));
}

void TcpServer::handle_accept(std::shared_ptr<ClientServer> client, const boost::system::error_code& err)
{
    std::cout << "client connect to server" << std::endl;
    if (!err) {
        client->start();
        this->_clients.push_back(std::make_shared<ClientServer>(this->_io_context));
        this->_acceptor.async_accept(this->_clients[this->_clients.size() - 1]->getSocket(),
                boost::bind(&TcpServer::handle_accept, this, this->_clients[this->_clients.size() - 1], boost::asio::placeholders::error));
    } else {
        std::cerr << "err: " << err.message() << std::endl;
        client.reset();
        this->_clients.pop_back();
    }

}