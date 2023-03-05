/*
** EPITECH PROJECT, 2023
** UdpServerSystem.hpp
** File description:
** UdpServerSystem
*/

#include "UdpClientSystem.hpp"

namespace rtype {

    UdpClientSystem::UdpClientSystem(boost::asio::io_context &ioc, std::string ip, std::string port, std::shared_ptr<Services::IService> services) : AUdpClientSystem("UdpClient"), _service(services), _resolver(ioc), _query(udp::v4(), ip, port), _receiver_endpoint(*_resolver.resolve(_query)), _socket(ioc), _nullscene(0), _nullstring("")
    {
        std::cout << "UDP CLIENT SYSTEM" << std::endl;
    }

    UdpClientSystem::~UdpClientSystem()
    {
    }

    void UdpClientSystem::start_receive()
    {
        this->_socket.async_receive_from(boost::asio::buffer(this->_buffer),
                                        this->_receiver_endpoint,
                                        boost::bind(&UdpClientSystem::handler_received, this,
                                                    boost::asio::placeholders::error,
                                                    boost::asio::placeholders::bytes_transferred));
    }

    void UdpClientSystem::send_data(size_t s_id,std::string text)
    {
        Serialize::Data info = Serialize::createData<Serialize::Data>(s_id, text);
        std::string data = Serialize::serialize<Serialize::Data>(info);
        this->_socket.async_send_to(boost::asio::buffer(data), this->_receiver_endpoint,
                            boost::bind(&UdpClientSystem::handler_send, this,
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
    }

    const std::string &UdpClientSystem::getName() const
    {
        return this->_nullstring; 
    }

    bool UdpClientSystem::isGameStillPlaying()
    { 
        return true; 
    }

    const size_t &UdpClientSystem::getCurrentScene() const
    { 
        return this->_nullscene; 
    }

    void UdpClientSystem::init() 
    {
        this->_socket.open(udp::v4());
        this->send_data(Services::Command::CONNECTED, "");
        this->start_receive();
    }

    void UdpClientSystem::update(std::shared_ptr<IScene> &scene)
    {
        if (!this->_queue.empty()) {
            this->_service->callService(this->_queue.front(), *scene);
            this->_queue.pop();
        }
    }

    void UdpClientSystem::destroy()
    {
        Serialize::Data info = Serialize::createData<Serialize::Data>(Services::Command::DISCONNECTED, "");
        std::string data = Serialize::serialize<Serialize::Data>(info);
        this->_socket.async_send_to(boost::asio::buffer(data), this->_receiver_endpoint,
                                    boost::bind(&UdpClientSystem::handler_quit, this,
                                    boost::asio::placeholders::error,
                                    boost::asio::placeholders::bytes_transferred));
    }

    std::pair<size_t, size_t> UdpClientSystem::getWindowWSize() const
    {
        return std::make_pair(0, 0);
    }

    void UdpClientSystem::handler_quit(const boost::system::error_code & /*error*/, std::size_t /*bytes_transferred*/)
    {
        std::cout << "sent quit to server" << std::endl;
        this->_socket.close();
    }

    void UdpClientSystem::handler_received(const boost::system::error_code &error, std::size_t size) 
    {
        if (!error && error != boost::asio::error::eof && size > 0) {
            std::cout << "On Received" << std::endl;
            Serialize::Data received_data = Serialize::deserialize<Serialize::Data>(std::string(this->_buffer.data(), size), size);
            this->_queue.push(received_data);
        }
        if (error == boost::asio::error::eof) {
            std::cout << "Server closed: " << this->_receiver_endpoint << std::endl;
        }
        if (error) {
            std::cout << "Error: " << error.message() << std::endl;
            return;
        }
        this->_socket.async_receive_from(boost::asio::buffer(this->_buffer),
                                        this->_receiver_endpoint,
                                        boost::bind(&UdpClientSystem::handler_received, this,
                                                    boost::asio::placeholders::error,
                                                    boost::asio::placeholders::bytes_transferred));
    }

    void UdpClientSystem::handler_send(const boost::system::error_code & /*error*/, std::size_t /*bytes_transferred*/)
    {
        std::cout << "sent to client" << std::endl;
    }
}