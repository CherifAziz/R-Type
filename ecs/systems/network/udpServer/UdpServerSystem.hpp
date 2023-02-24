/*
** EPITECH PROJECT, 2023
** UdpServerSystem.hpp
** File description:
** UdpServerSystem
*/

#ifndef UDPSERVERSYSTEM_HPP_
    #define UDPSERVERSYSTEM_HPP_

    #include "AUdpServerSystem.hpp"
    #include "Serialize.hpp"
    #include "IServices.hpp"
    #include <optional>
    #include <iostream>
    #include <string>
    #include <memory>
    #include <map>
    #include <queue>
    #include <vector>
    #include <boost/array.hpp>
    #include <boost/bind/bind.hpp>
    #include <boost/shared_ptr.hpp>
    #include <boost/asio.hpp>
    #include <boost/unordered_map.hpp>

    using namespace boost::asio;
    using namespace boost::asio::ip;
    using namespace boost::placeholders;

    namespace rtype {
        class UdpClient {
            public:
                UdpClient(std::size_t id, udp::endpoint endpoint, udp::socket &socket) : _endpoint(endpoint), _serverSocket(socket) {
                    std::cout << "UdpClient Added" << std::endl;
                };

                void sendDataToClient(Serialize::Data data) {
                    std::string data_to_send = Serialize::serialize<Serialize::Data>(data);
                    this->_serverSocket.async_send_to(boost::asio::buffer(data_to_send), this->_endpoint,
                                        boost::bind(&UdpClient::handler_send, this,
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
                };

                udp::endpoint &getEndpoint() {
                    return this->_endpoint;
                };

                void handler_send(const boost::system::error_code &error, std::size_t bytes_transferred) {
                    if (error) {
                        std::cout << "Error: " << error.message() << std::endl;
                    } else {
                        std::cout << "Sent data" << std::endl;
                    }
                };

                void addToListOfCommands(Serialize::Data &data) {
                    this->_listOfCommands.push(data);
                };

                std::optional<Serialize::Data> getCommand() {
                    try {
                        if (this->_listOfCommands.empty())
                            return std::nullopt;
                        Serialize::Data data = this->_listOfCommands.front();
                        this->_listOfCommands.pop();
                        return data;
                    } catch (std::exception &e) {
                        std::cout << "Error: " << e.what() << std::endl;
                        return std::nullopt;
                    }
                };

                ~UdpClient() {
                    std::cout << "UdpClient removed" << std::endl;
                };

            private:
                udp::socket &_serverSocket;
                udp::endpoint _endpoint;
                boost::array<char, 1024> _data;
                std::queue<Serialize::Data> _listOfCommands;
        };

        class UdpServerSystem : public AUdpServerSystem {
            public:
                UdpServerSystem(boost::asio::io_service &io_service, int port, std::shared_ptr<Services::IService> services) : AUdpServerSystem("UdpServer"), _service(services), _socker(io_service, udp::endpoint(boost::asio::ip::udp::v4(), port)), _nullscene(0), _nullstring("") {
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

                void send_data(int s_id, std::string text, boost::asio::ip::udp::endpoint endpoint) {
                    Serialize::Data info = Serialize::createData<Serialize::Data>(s_id, text);
                    this->_clients[endpoint]->sendDataToClient(info);
                };

                void init() {};
                const std::string &getName() const { return this->_nullstring; };
                bool isGameStillPlaying() { return true; };
                const size_t &getCurrentScene() const { return this->_nullscene; };

                void update(std::shared_ptr<IScene> &scene) {
                    for (auto &client : this->_clients) {
                        std::optional<Serialize::Data> data = client.second->getCommand();
                        if (data != std::nullopt) {
                            client.second->getEndpoint();
                            data.value().printData();
                            std::cout << this->_service << std::endl;
                            this->_service->callService(client.second->getEndpoint(), this->_clients, data.value(), *scene);
                        }
                    }
                };

                void destroy() {};

                std::pair<size_t, size_t> getWindowWSize() const {
                    return std::make_pair(0, 0);
                };

                ~UdpServerSystem() {};

            protected:
            private:
                void handler_received(const boost::system::error_code &error, std::size_t size) {
                    std::cout << "On Received" << std::endl;
                    if (!error && error != boost::asio::error::eof && size > 0) {
                        if (this->_clients.find(this->_remote_endpoint) == this->_clients.end())
                            this->_clients[this->_remote_endpoint] = std::make_unique<UdpClient>(this->_clients.size() + 1, this->_remote_endpoint, this->_socker);
                        std::cout << size << sizeof(Serialize::Data) << std::endl;
                        if (size >= sizeof(Serialize::Data)) {
                            std::cout << "Received data" << std::endl;
                            Serialize::Data info = Serialize::deserialize<Serialize::Data>(std::string(this->_data.data(), size), size);
                            // info.printData();
                            this->_clients[this->_remote_endpoint]->addToListOfCommands(info);
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
                std::shared_ptr<Services::IService> _service;
                std::map<udp::endpoint, std::unique_ptr<UdpClient>> _clients;
                const std::string _nullstring;
                const size_t _nullscene;
        };
    }

#endif /* !UDPSERVERSYSTEM_HPP_ */
