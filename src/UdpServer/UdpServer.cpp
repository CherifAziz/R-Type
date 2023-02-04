#include "./UdpServer.hpp"

UdpServer::UdpServer(boost::asio::io_service &io_service, int port) : _socker(io_service, udp::endpoint(udp::v4(), port))
{
    std::cout << "UdpServer Created" << std::endl;
    this->start_receive();
}

void UdpServer::start_receive()
{
    this->_socker.async_receive_from(boost::asio::buffer(this->_buffer),
                                     this->_remote_endpoint,
                                     boost::bind(&UdpServer::handler_received, this,
                                                 boost::asio::placeholders::error,
                                                 boost::asio::placeholders::bytes_transferred));
}

void UdpServer::handler_received(const boost::system::error_code &error,
                              std::size_t /*bytes_transferred*/)
{
    std::cout << "Received" << std::endl;
    if (!error || error == boost::asio::error::message_size)
    {
        std::cout << this->_buffer.c_array() << std::endl;
        this->send_data();
        this->_socker.async_receive_from(boost::asio::buffer(this->_buffer),
                                     this->_remote_endpoint,
                                     boost::bind(&UdpServer::handler_received, this,
                                                 boost::asio::placeholders::error,
                                                 boost::asio::placeholders::bytes_transferred));
    }
}

void UdpServer::send_data()
{
    boost::shared_ptr<std::string> message(
                new std::string("message from UdpServer\n"));

    this->_socker.async_send_to(boost::asio::buffer(*message), this->_remote_endpoint,
                        boost::bind(&UdpServer::handler_send, this, message,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
}

void UdpServer::handler_send(boost::shared_ptr<std::string> /*message*/,
                          const boost::system::error_code & /*error*/,
                          std::size_t /*bytes_transferred*/)
{
    std::cout << "sent to client" << std::endl;
}

UdpServer::~UdpServer()
{
    std::cout << "UdpServer Destroy" << std::endl;
};