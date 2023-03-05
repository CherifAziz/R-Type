/*
** EPITECH PROJECT, 2023
** ClientSystem
** File description:
** ClientSystem
*/

#include "TcpClientSystem.hpp"

namespace rtype {

    TcpClientSystem::TcpClientSystem(boost::asio::io_context &ioc, std::string IpServer, int portServer) : _socket(ioc), ATcpClientSystem("ClientSystem") 
    {
        std::cout << "Client started" << std::endl;
        tcp::endpoint endpoint(boost::asio::ip::address::from_string(IpServer), portServer);
        _socket.async_connect(endpoint, boost::bind(&TcpClientSystem::onConnect, this, boost::asio::placeholders::error));
    }

    TcpClientSystem::~TcpClientSystem()
    {
    }

    const std::string &TcpClientSystem::getName() const 
    { 
        return (""); 
    }

    bool TcpClientSystem::isGameStillPlaying() 
    { 
        return true; 
    }

    const size_t &TcpClientSystem::getCurrentScene() const 
    { 
        return 0; 
    }

    void TcpClientSystem::start_receive() 
    {
        std::cout << "start receive" << std::endl;
        boost::asio::async_read(this->_socket, boost::asio::buffer(this->data_), boost::asio::transfer_at_least(1), boost::bind(&TcpClientSystem::onReceive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }

    void TcpClientSystem::sendDataToServer(std::string data) 
    {
        Serialize::Data info = { 43, data };
        std::string data_seria = Serialize::serialize<Serialize::Data>(info);
        boost::asio::async_write(this->_socket, boost::asio::buffer(data_seria), boost::bind(&TcpClientSystem::onSent, this, boost::asio::placeholders::error));
    }

    void TcpClientSystem::destroy()
    {
        this->_socket.close();
    }

    std::pair<size_t, size_t> TcpClientSystem::getWindowWSize() const
    {
        return std::make_pair(0, 0);
    }

    void TcpClientSystem::onReceive(const boost::system::error_code& err, std::size_t size) 
    {
        std::cout << "On Received" << std::endl;
        if (err && err != boost::asio::error::eof) {
            std::cerr << err.message() << std::endl;
            return;
        }
        if (err == boost::asio::error::eof)
            return;
        Serialize::Data received_data = Serialize::deserialize<Serialize::Data>(std::string(this->data_.data(), size), size);
        boost::asio::async_read(this->_socket, boost::asio::buffer(this->data_), boost::asio::transfer_at_least(1), boost::bind(&TcpClientSystem::onReceive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    };

    void TcpClientSystem::onSent(const boost::system::error_code& err)
    {
        std::cout << "On Sent" << std::endl;
        if (err) {
            std::cerr << err.message() << std::endl;
            return;
        }
    };

    void TcpClientSystem::onConnect(const boost::system::error_code& err)
     {
        std::cout << "Conneted to server" << std::endl;
        if (!err) {
            std::cout << "Connected to server" << std::endl;
            this->start_receive();
        } else {
            std::cerr << err.message() << std::endl;
        }
    };
}