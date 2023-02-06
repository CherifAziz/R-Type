/*
** EPITECH PROJECT, 2023
** Client
** File description:
** Client
*/

#include "Client.hpp"

Client::Client(boost::asio::io_context &ioc, std::string ip, int port) : _socket(ioc), _message("")
{
    tcp::endpoint endpoint(boost::asio::ip::address::from_string(ip), port);
    try {
        this->_socket.connect(endpoint);
        this->start_receive();
    } catch (std::exception &err) {
        std::cout << "error => " << err.what() << std::endl;
    }
}

Client::~Client()
{
    this->_socket.close();
}

void Client::start_receive()
{
    std::cout << "start_receive function" << std::endl;
    boost::asio::async_read(this->_socket, boost::asio::buffer(this->data_), boost::asio::transfer_at_least(1) , boost::bind(&Client::onReceive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    std::cout << "end" << std::endl;
}

void Client::onReceive(const boost::system::error_code &err, std::size_t size)
{
    std::cout << "On Received" << std::endl;
    if (err && err != boost::asio::error::eof)
    {
        std::cerr << err.message() << std::endl;
        return;
    }
    Data_t received_data;
    std::stringstream archive_stream;
    archive_stream.write(data_.data(), size);
    boost::archive::binary_iarchive archive(archive_stream);
    archive >> received_data;
    std::cout << "Received data: " << received_data.s_id << ", " << received_data.test << std::endl;
    boost::asio::async_read(this->_socket, boost::asio::buffer(this->data_), boost::asio::transfer_at_least(1) , boost::bind(&Client::onReceive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void Client::sendDataToServer(std::string /*data*/)
{
    Data_t info = { 43, "Coucou du client" };
    std::ostringstream os;
    boost::archive::binary_oarchive archive(os);
    archive << info;
    std::string data = os.str();
    boost::asio::async_write(this->_socket, boost::asio::buffer(data), boost::bind(&Client::onSent, this, boost::asio::placeholders::error));
}

void Client::onSent(const boost::system::error_code &err)
{
    if (err && err != boost::asio::error::eof)
    {
        std::cerr << err.message() << std::endl;
        return;
    }
    std::cout << "message sent to server" << std::endl;
}