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
    #include "Storage.hpp"
    #include "IServices.hpp"
    #include "Storage.hpp"
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
                UdpClient(udp::endpoint endpoint, udp::socket &socket) : _endpoint(endpoint), _serverSocket(socket) {
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

                boost::uuids::uuid &getUuid() {
                    return this->_uuid;
                };

                void setUuid(boost::uuids::uuid uuid) {
                    this->_uuid = uuid;
                };

                entity_t &getEntity() {
                    return this->_entity;
                };

                void setEntity(entity_t entity) {
                    this->_entity = entity;
                };

                void handler_send(const boost::system::error_code &error, std::size_t bytes_transferred) {
                    if (error) {
                        std::cout << "Error: " << error.message() << std::endl;
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
                boost::uuids::uuid _uuid;
                entity_t _entity;
        };

        class ClientManager {
            public:
                ClientManager() {};
                ~ClientManager() {};

                void addClient(udp::endpoint endpoint,  udp::socket &socket) {
                    this->_clients[endpoint] = std::make_unique<UdpClient>(endpoint, socket);
                };

                void removeClient(udp::endpoint endpoint) {
                    if (this->_clients.find(endpoint) != this->_clients.end())
                        this->_clients.erase(endpoint);
                };

                std::optional<UdpClient * const> getClient(udp::endpoint endpoint) {
                    if (this->_clients.find(endpoint) == this->_clients.end())
                        return std::nullopt;
                    else
                        return this->_clients[endpoint].get();
                };

                void sendToEachClient(Serialize::Data data) {
                    for (auto &client : this->_clients) {
                        client.second->sendDataToClient(data);
                    }
                };

                std::map<udp::endpoint, std::unique_ptr<UdpClient>> &getClients() {
                    return this->_clients;
                };

            private:
                std::map<udp::endpoint, std::unique_ptr<UdpClient>> _clients;
        };

        class UdpServerSystem : public AUdpServerSystem {
            public:
                UdpServerSystem(boost::asio::io_service &io_service, int port, std::shared_ptr<Services::IService> services) : AUdpServerSystem("UdpServer"), _service(services), _socker(io_service, udp::endpoint(boost::asio::ip::udp::v4(), port)), _nullscene(0), _nullstring(""), _storage(Storage::getStorage()) {
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
                    Serialize::Data info = Serialize::createData<Serialize::Data>(s_id, {});
                    if (this->_clients.getClient(endpoint) != std::nullopt)
                        this->_clients.getClient(endpoint).value()->sendDataToClient(info);
                };

                void init() {};

                const std::string &getName() const { return this->_nullstring; };
                bool isGameStillPlaying() { return _storage->isStillPlaying(); };
                const size_t &getCurrentScene() const { return this->_nullscene; };

                void update(std::shared_ptr<IScene> &scene) {
                    for (auto &client : this->_clients.getClients()) {
                        std::optional<Serialize::Data> data = client.second->getCommand();
                        if (data != std::nullopt) {
                            this->_service->callService(client.second->getEndpoint(), this->_clients, data.value(), *scene);
                            if (data.value().s_id == Services::Command::DISCONNECTED)
                                return;
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
                    if (!error && error != boost::asio::error::eof && size > 0) {
                        if (this->_clients.getClient(this->_remote_endpoint) == std::nullopt)
                            this->_clients.addClient(this->_remote_endpoint, this->_socker);
                        if (size >= sizeof(Serialize::Data)) {
                            Serialize::Data info = Serialize::deserialize<Serialize::Data>(std::string(this->_data.data(), size), size);
                            if (this->_clients.getClient(this->_remote_endpoint) != std::nullopt)
                                this->_clients.getClient(this->_remote_endpoint).value()->addToListOfCommands(info);
                            else
                                std::cout << "Client not found" << std::endl;
                        }
                    }
                    if (error == boost::asio::error::eof) {
                        std::cout << "Client disconnected: " << this->_remote_endpoint << std::endl;
                        this->_clients.removeClient(this->_remote_endpoint);
                    }
                    if (error) {
                        std::cout << "Handler_recieved -> Error: " << error.message() << std::endl;
                    }
                    this->_socker.async_receive_from(boost::asio::buffer(this->_data),
                                                    this->_remote_endpoint,
                                                    boost::bind(&UdpServerSystem::handler_received, this,
                                                                boost::asio::placeholders::error,
                                                                boost::asio::placeholders::bytes_transferred));
                };

                void handler_send(const boost::system::error_code &err, std::size_t /*bytes_transferred*/) {
                    if (err) {
                        std::cerr << err.what() << std::endl;
                    }
                };
                std::shared_ptr<Storage> _storage;
                udp::socket _socker;
                udp::endpoint _remote_endpoint;
                std::array<char, 1024> _data;
                std::shared_ptr<Services::IService> _service;
                ClientManager _clients;
                const std::string _nullstring;
                const size_t _nullscene;
                std::shared_ptr<Storage> _storage;

        };
    }

#endif /* !UDPSERVERSYSTEM_HPP_ */
