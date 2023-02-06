/*
** EPITECH PROJECT, 2023
** ClientServer
** File description:
** ClientServer
*/

#include "ClientServer.hpp"

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
    Data_t info = { 12, "Coucou du serveur" };
    std::ostringstream os;
    boost::archive::binary_oarchive archive(os);
    archive << info;
    std::string data = os.str();
    boost::asio::async_write(this->_socket, boost::asio::buffer(data), boost::bind(&ClientServer::onWrite, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    this->start_read();
}

void ClientServer::onWrite(const boost::system::error_code& err, size_t size)
{
    std::cout << "message sent : " << size  << std::endl;
}

void ClientServer::start_read()
{
    std::cout << "listen client" << std::endl;
    boost::asio::async_read(this->_socket, boost::asio::buffer(this->data_), boost::asio::transfer_at_least(1), boost::bind(&ClientServer::onRead, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void ClientServer::onRead(const boost::system::error_code& err, size_t size)
{
    if (err && err != boost::asio::error::eof) {
        std::cerr << err.message() << std::endl;
        return;
    }
    Data_t received_data;
    std::stringstream archive_stream;
    archive_stream.write(data_.data(), size);
    boost::archive::binary_iarchive archive(archive_stream);
    archive >> received_data;
    std::cout << "Received data from client: " << received_data.s_id << ", " << received_data.test << std::endl;
    boost::asio::async_read(this->_socket, boost::asio::buffer(this->data_), boost::asio::transfer_at_least(1) , boost::bind(&ClientServer::onRead, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}