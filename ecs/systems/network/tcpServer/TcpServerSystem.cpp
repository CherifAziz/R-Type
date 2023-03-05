/*
** EPITECH PROJECT, 2023
** ServerSystem
** File description:
** ServerSystem
*/

#include "TcpServerSystem.hpp"

namespace rtype {

    ClientServer::ClientServer(boost::asio::io_context& io_context): _socket(io_context)
    {
    }

    ClientServer::~ClientServer() 
    {
        this->_socket.close();
    }

    tcp::socket &ClientServer::getSocket() 
    { 
        return this->_socket; 
    }

    void ClientServer::start() 
    {
        std::cout << "client started" << std::endl;
        Serialize::Data info = Serialize::createData<Serialize::Data>(0, "");
        std::string data = Serialize::serialize<Serialize::Data>(info);
        boost::asio::async_write(this->_socket, boost::asio::buffer(data), boost::bind(&ClientServer::onWrite, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
        // sleep(2);
        boost::asio::async_write(this->_socket, boost::asio::buffer(data), boost::bind(&ClientServer::onWrite, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
        this->start_read();
    }

    void ClientServer::start_read() 
    {
        boost::asio::async_read(this->_socket, boost::asio::buffer(this->data_), boost::asio::transfer_at_least(1), boost::bind(&ClientServer::onRead, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }

    void ClientServer::onRead(const boost::system::error_code& err, size_t size) 
    {
        if (err && err != boost::asio::error::eof) {
            std::cerr << err.message() << std::endl;
            return;
        }
        if (err == boost::asio::error::eof)
            return;
        Serialize::Data received_data = Serialize::deserialize<Serialize::Data>(std::string(this->data_.data(), size), size);
        boost::asio::async_read(this->_socket, boost::asio::buffer(this->data_), boost::asio::transfer_at_least(1), boost::bind(&ClientServer::onRead, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }

    void ClientServer::onWrite(const boost::system::error_code& err, size_t size) 
    {
        std::cout << "message sent : " << size  << std::endl;
        if (err)
            std::cout << err.message() << std::endl;
    }

    TcpServerSystem::TcpServerSystem(boost::asio::io_context& ioc, int port) : ATcpServerSystem("TcpServer"), _acceptor(ioc, tcp::endpoint(tcp::v4(), port)), _io_context(ioc), _storage(Storage::getStorage())
    {
        std::cout << "ServerSystem created" << std::endl;
        this->start_accept();
    };

    TcpServerSystem::~TcpServerSystem()
    {
    }

    void TcpServerSystem::start_accept()
    {
        std::cout << "start accept" << std::endl;
        this->_clients.push_back(std::make_shared<ClientServer>(this->_io_context));
        this->_acceptor.async_accept(this->_clients[this->_clients.size() - 1]->getSocket(),
            boost::bind(&TcpServerSystem::handle_accept, this, this->_clients[this->_clients.size() - 1], boost::asio::placeholders::error));
    }

    void TcpServerSystem::handle_accept(std::shared_ptr<ClientServer> client, const boost::system::error_code& err)
    {
        std::cout << "client connect to server" << std::endl;
        if (!err) {
            client->start();
            this->_clients.push_back(std::make_shared<ClientServer>(this->_io_context));
            this->_acceptor.async_accept(this->_clients[this->_clients.size() - 1]->getSocket(),
                    boost::bind(&TcpServerSystem::handle_accept, this, this->_clients[this->_clients.size() - 1], boost::asio::placeholders::error));
        } else {
            std::cerr << "err: " << err.message() << std::endl;
            client.reset();
            this->_clients.pop_back();
        }
    }

    const std::string &TcpServerSystem::getName() const
    { 
        return ("");
    }

    bool TcpServerSystem::isGameStillPlaying()
    { 
        return _storage->getRenderWindow().isOpen() && _storage->isStillPlaying();
    }
                
    const size_t &TcpServerSystem::getCurrentScene() const
    { 
        return 0; 
    }

    std::pair<size_t, size_t> TcpServerSystem::getWindowWSize() const
    {
        return std::make_pair(0, 0);
    }
}