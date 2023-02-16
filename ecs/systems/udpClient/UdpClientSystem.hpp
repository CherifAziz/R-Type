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
    #include <boost/archive/binary_oarchive.hpp>
    #include <boost/archive/binary_iarchive.hpp>
    #include <boost/serialization/serialization.hpp>
    #include "AUdpClientSystem.hpp"

    using namespace boost::asio;
    using namespace boost::asio::ip;

    namespace Serialize {
        struct Data {
            int size;
            std::string _data;
            template<typename Ar> void serialize(Ar& ar, unsigned) {
                ar & size & _data;
            }
        };

        template<typename T>
        std::string serialize(T &data) {
            std::ostringstream os;
            boost::archive::binary_oarchive archive(os);
            archive << data;
            return os.str();
        }

        template<typename T>
        T deserialize(std::string data, size_t size) {
            T received_data;
            std::stringstream archive_stream;
            archive_stream.write(data.data(), size);
            boost::archive::binary_iarchive archive(archive_stream);
            archive >> received_data;
            return received_data;
        }
    };

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
                void destroy() {};
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
