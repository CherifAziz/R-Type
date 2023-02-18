/*
** EPITECH PROJECT, 2023
** UdpServerSystem.hpp
** File description:
** UdpServerSystem
*/

#ifndef UDPCLIENTSYSTEM_HPP_
    #define UDPCLIENTSYSTEM_HPP_

    #include "IServices.hpp"
    #include "Serialize.hpp"
    #include <iostream>
    #include <string>
    #include <unordered_map>
    #include <map>
    #include <boost/array.hpp>
    #include <boost/bind/bind.hpp>
    #include <boost/shared_ptr.hpp>
    #include <boost/asio.hpp>
    #include <boost/unordered_map.hpp>
    #include "AUdpClientSystem.hpp"

    using namespace boost::asio;
    using namespace boost::asio::ip;

    namespace rtype {
        class UdpClientSystem : public AUdpClientSystem {
            public:
                UdpClientSystem(boost::asio::io_context &ioc, std::string ip, std::string port) : AUdpClientSystem("UdpClient"), _resolver(ioc), _query(udp::v4(), ip, port), _receiver_endpoint(*_resolver.resolve(_query)), _socket(ioc), _id(0) {
                    this->_socket.open(udp::v4());
                    this->send_data(Services::Type::COMMAND, Services::Command::CONNECTED, "");
                    this->start_receive();
                }

                void start_receive() {
                    this->_socket.async_receive_from(boost::asio::buffer(this->_buffer),
                                                    this->_receiver_endpoint,
                                                    boost::bind(&UdpClientSystem::handler_received, this,
                                                                boost::asio::placeholders::error,
                                                                boost::asio::placeholders::bytes_transferred));
                };

                void send_data(Services::Type type, size_t s_id,std::string text) {
                    Serialize::Data info = Serialize::createData<Serialize::Data>(Services::Type::COMMAND, this->_id, s_id, text);
                    std::string data = Serialize::serialize<Serialize::Data>(info);
                    this->_socket.async_send_to(boost::asio::buffer(data), this->_receiver_endpoint,
                                        boost::bind(&UdpClientSystem::handler_send, this,
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
                };

                void init() {};
                void update(ComponentManager &/*componentManager*/, EntityManager &/*entityManager*/) {};
                void destroy() {
                    this->_socket.close();
                };
                std::pair<size_t, size_t> getWindowWSize() const {
                    return std::make_pair(0, 0);
                };
                ~UdpClientSystem() {};

            private:
                void handler_received(const boost::system::error_code &error, std::size_t size) {
                    if (!error && error != boost::asio::error::eof && size > 0) {
                        std::cout << "On Received" << std::endl;
                        Serialize::Data received_data = Serialize::deserialize<Serialize::Data>(std::string(this->_buffer.data(), size), size);
                        received_data.printData();
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
                };

                void handler_send(const boost::system::error_code & /*error*/, std::size_t /*bytes_transferred*/) {
                    std::cout << "sent to client" << std::endl;
                };

                udp::resolver _resolver;
                udp::resolver::query _query;
                udp::endpoint _receiver_endpoint;
                udp::socket _socket;
                std::array<char, 1024> _buffer;
                std::size_t _id;
        };
    }

#endif /* !UDPCLIENTSYSTEM_HPP_ */
