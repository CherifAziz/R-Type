/*
** EPITECH PROJECT, 2023
** UdpServerSystem.hpp
** File description:
** UdpServerSystem
*/

#ifndef UDPSERVERSYSTEM_HPP_
    #define UDPSERVERSYSTEM_HPP_
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
    #include "AUdpServerSystem.hpp"

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
        class UdpServerSystem : public AUdpServerSystem {
            public:
                UdpServerSystem(boost::asio::io_service &io_service, int port) : AUdpServerSystem("UdpServer"), _socker(io_service, udp::endpoint(boost::asio::ip::udp::v4(), port)){
                    std::cout << "UdpServer Created" << std::endl;
                    this->start_receive();
                };

                void start_receive() {
                    this->_socker.async_receive_from(boost::asio::buffer(this->_data),
                                        this->_remote_endpoint,
                                        boost::bind(&UdpServerSystem::handler_received, this,
                                                    boost::asio::placeholders::error,
                                                    boost::asio::placeholders::bytes_transferred));
                };

                void send_data(std::string text, boost::asio::ip::udp::endpoint &endpoint) {
                    Serialize::Data info = { 0, "Connected to UdpServer" };
                    std::string data = Serialize::serialize<Serialize::Data>(info);
                    this->_socker.async_send_to(boost::asio::buffer(data), this->_remote_endpoint,
                                        boost::bind(&UdpServerSystem::handler_send, this,
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
                };
                void init() {};
                void update(ComponentManager &/*componentManager*/, EntityManager &/*entityManager*/) {};
                void destroy() {};
                std::pair<size_t, size_t> getWindowWSize() const {
                    return std::make_pair(0, 0);
                };
                ~UdpServerSystem() {};

            protected:
            private:
                void handler_received(const boost::system::error_code &error, std::size_t size) {
                    if (!error && error != boost::asio::error::eof && size > 0) {
                        std::cout << "On Received" << std::endl;
                        if (size == sizeof(Serialize::Data)) {
                            Serialize::Data info = Serialize::deserialize<Serialize::Data>(this->_data.data(), size);
                            std::cout << "Received from client: " << this->_remote_endpoint << " : " << info._data << " - " << info.size << std::endl;
                        }
                        if (this->_clients.find(this->_remote_endpoint) == this->_clients.end()) {
                            this->send_data("Connected to UdpServer", this->_remote_endpoint);
                            for (auto &client : this->_clients)
                                this->_socker.send_to(boost::asio::buffer("New client connected: " + this->_remote_endpoint.address().to_string() + "\n"), client.first);
                            this->_clients[this->_remote_endpoint] = std::string();
                        }
                    }
                    if (error == boost::asio::error::eof) {
                        std::cout << "Client disconnected: " << this->_remote_endpoint << std::endl;
                        this->_clients.erase(this->_remote_endpoint);
                    }
                    if (error) {
                        std::cout << "Error: " << error.message() << std::endl;
                    }
                    this->_socker.async_receive_from(boost::asio::buffer(this->_data),
                                                    this->_remote_endpoint,
                                                    boost::bind(&UdpServerSystem::handler_received, this,
                                                                boost::asio::placeholders::error,
                                                                boost::asio::placeholders::bytes_transferred));
                };

                void handler_send(const boost::system::error_code &/*error*/, std::size_t /*bytes_transferred*/) {
                    std::cout << "sent to client" << std::endl;
                };

                udp::socket _socker;
                udp::endpoint _remote_endpoint;
                std::array<char, 1024> _data;
                std::map<udp::endpoint, std::string> _clients;
        };
    }

#endif /* !UDPSERVERSYSTEM_HPP_ */
