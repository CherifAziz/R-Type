/*
** EPITECH PROJECT, 2023
** UdpServerSystem.hpp
** File description:
** UdpServerSystem
*/

#ifndef UDPCLIENTSYSTEM_HPP_
    #define UDPCLIENTSYSTEM_HPP_
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
    #include "Serialize.hpp"

    using namespace boost::asio;
    using namespace boost::asio::ip;

    namespace rtype {
        class UdpClientSystem : public AUdpClientSystem {
            public:
                UdpClientSystem(boost::asio::io_context &ioc, std::string ip, std::string port) : AUdpClientSystem("UdpClient"), _resolver(ioc), _query(udp::v4(), ip, port), _receiver_endpoint(*_resolver.resolve(_query)), _socket(ioc) {
                    this->_socket.open(udp::v4());
                    std::array<char, 1> send_buf  = { 0 };
                    this->_socket.send_to(boost::asio::buffer(send_buf), this->_receiver_endpoint);
                }
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
                udp::resolver _resolver;
                udp::resolver::query _query;
                udp::endpoint _receiver_endpoint;
                udp::socket _socket;
        };
    }

#endif /* !UDPCLIENTSYSTEM_HPP_ */
