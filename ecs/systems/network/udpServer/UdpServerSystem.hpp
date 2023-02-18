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

    namespace rtype {
        class UdpClient {
            public:
                UdpClient(std::size_t id, udp::endpoint endpoint, udp::socket &socket) : _id(id), _endpoint(endpoint), _serverSocket(socket) {
                    std::cout << "UdpClient Added" << std::endl;
                };

                std::size_t getId() const {
                    return this->_id;
                };

                void sendDataToClient(Serialize::Data data) {
                    std::string data_to_send = Serialize::serialize<Serialize::Data>(data);
                    this->_serverSocket.async_send_to(boost::asio::buffer(data_to_send), this->_endpoint,
                                        boost::bind(&UdpClient::handler_send, this,
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
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
                std::size_t _id;
                udp::socket &_serverSocket;
                udp::endpoint _endpoint;
                boost::array<char, 1024> _data;
                std::queue<Serialize::Data> _listOfCommands;
        };

        class UdpServerSystem : public AUdpServerSystem {
            public:
                UdpServerSystem(boost::asio::io_service &io_service, int port, std::unique_ptr<Services::IService> services) : AUdpServerSystem("UdpServer"), _service(std::move(services)), _socker(io_service, udp::endpoint(boost::asio::ip::udp::v4(), port))    {
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

                void send_data(Services::Type type, int s_id, std::string text, boost::asio::ip::udp::endpoint endpoint) {
                    Serialize::Data info = Serialize::createData<Serialize::Data>(type, 0, s_id, text);
                    std::string data = Serialize::serialize<Serialize::Data>(info);
                    this->_socker.async_send_to(boost::asio::buffer(data), endpoint,
                                        boost::bind(&UdpServerSystem::handler_send, this,
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
                };

                void init() {};
                const std::string &getName() const { return (""); };
                bool isGameStillPlaying() { return true; };
                const size_t &getCurrentScene() const { return 0; };

                void update(std::shared_ptr<IScene> &scene) {
                    for (auto &client : this->_clients) {
                        std::optional<Serialize::Data> data = client.second->getCommand();
                        if (data != std::nullopt) {
                            // this->_service->callService(this->_clients, data.value(), scene., Entity);
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
                        if (this->_clients.find(this->_remote_endpoint) == this->_clients.end()) {
                            // for (auto &client : this->_clients)
                            //     this->send_data(1, std::to_string(this->_clients.size() + 1), client.first);
                            this->_clients[this->_remote_endpoint] = std::make_unique<UdpClient>(this->_clients.size() + 1, this->_remote_endpoint, this->_socker);
                            this->_clients[this->_remote_endpoint]->sendDataToClient(Serialize::createData<Serialize::Data>(Services::Type::COMMAND, 0, this->_clients.size(), "Connected to server"));
                        }
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
                std::unique_ptr<Services::IService> _service;
                std::map<udp::endpoint, std::unique_ptr<UdpClient>> _clients;
        };
    }

#endif /* !UDPSERVERSYSTEM_HPP_ */
