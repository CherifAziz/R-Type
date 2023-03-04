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
    #include <map>
    #include <queue>
    #include <memory>
    #include <boost/array.hpp>
    #include <boost/bind/bind.hpp>
    #include <boost/shared_ptr.hpp>
    #include <boost/asio.hpp>
    #include <boost/unordered_map.hpp>
    #include "IServices.hpp"
    #include "Serialize.hpp"
    #include "AUdpClientSystem.hpp"
    #include "Storage.hpp"

    using namespace boost::asio;
    using namespace boost::placeholders;
    using namespace boost::asio::ip;

    namespace rtype {
        class UdpClientSystem : public AUdpClientSystem {
            public:
                UdpClientSystem(boost::asio::io_context &ioc, std::string ip, std::string port, std::shared_ptr<Services::IService> services) : AUdpClientSystem("UdpClient"), _service(services), _resolver(ioc), _query(udp::v4(), ip, port), _receiver_endpoint(*_resolver.resolve(_query)), _socket(ioc), _nullscene(0), _nullstring("") {
                    std::cout << "UDP CLIENT SYSTEM" << std::endl;
                }

                void start_receive() {
                    this->_socket.async_receive_from(boost::asio::buffer(this->_buffer),
                                                    this->_receiver_endpoint,
                                                    boost::bind(&UdpClientSystem::handler_received, this,
                                                                boost::asio::placeholders::error,
                                                                boost::asio::placeholders::bytes_transferred));
                };

                void send_data(Serialize::Data info) {
                    std::string data = Serialize::serialize<Serialize::Data>(info);
                    this->_socket.async_send_to(boost::asio::buffer(data), this->_receiver_endpoint,
                                        boost::bind(&UdpClientSystem::handler_send, this,
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
                };

                const std::string &getName() const { return this->_nullstring; };
                
                bool isGameStillPlaying() {
                    return this->_storage->getRenderWindow().isOpen();
                };
                /**
                 * @brief check the connection status
                 * 
                 * @return true if it's connected to the server, false otherwise
                 */
                bool isConnected()
                {
                    return _storage->isConnected();
                }
                const size_t &getCurrentScene() const { return this->_nullscene; };

                void init() {
                    this->_storage = Storage::getStorage();
                    this->_socket.open(udp::v4());
                    this->send_data(Serialize::createData<Serialize::Data>(Services::Command::CONNECTED, {}));
                    this->start_receive();
                };

                void update(std::shared_ptr<IScene> &scene) {
                    try {
                        std::optional<Serialize::Data> data = scene->getComponentManager().get<Network>(scene->getEntityManager().getEntitiesFromFamily("player")[0]->getId()).getCommands();
                        if (data.has_value())
                            this->_service->callService(data.value(), *this, *scene);
                    } catch (std::invalid_argument &e) {}

                    if (!this->_queue.empty()) {
                        this->_service->callService(this->_queue.front(), *this, *scene);
                        this->_queue.pop();
                    }
                };

                void destroy() {
                    Serialize::Data info = Serialize::createData<Serialize::Data>(Services::Command::DISCONNECTED, {});
                    std::string data = Serialize::serialize<Serialize::Data>(info);
                    this->_socket.async_send_to(boost::asio::buffer(data), this->_receiver_endpoint,
                                                boost::bind(&UdpClientSystem::handler_quit, this,
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));
                };

                std::pair<size_t, size_t> getWindowWSize() const {
                    return std::make_pair(0, 0);
                };

                ~UdpClientSystem() {};

            private:
                void handler_quit(const boost::system::error_code & /*error*/, std::size_t /*bytes_transferred*/) {
                    std::cout << "sent quit to server" << std::endl;
                    this->_socket.close();
                };

                void handler_received(const boost::system::error_code &error, std::size_t size) {
                    if (!error && error != boost::asio::error::eof && size > 0) {
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
                };

                void handler_send(const boost::system::error_code & err, std::size_t /*bytes_transferred*/) {
                    if (err) {
                        std::cerr << err.what() << std::endl;
                    }
                };

                /**
                 * @brief the singleton storage
                 *
                 */
                std::shared_ptr<Storage> _storage;
                udp::resolver _resolver;
                udp::resolver::query _query;
                udp::endpoint _receiver_endpoint;
                udp::socket _socket;
                std::array<char, 1024> _buffer;
                std::queue<Serialize::Data> _queue;
                std::shared_ptr<Services::IService> _service;
                const std::string _nullstring;
                const size_t _nullscene;
        };
    }

#endif /* !UDPCLIENTSYSTEM_HPP_ */
