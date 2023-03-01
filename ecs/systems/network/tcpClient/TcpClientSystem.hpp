/*
** EPITECH PROJECT, 2023
** ClientSystem
** File description:
** ClientSystem
*/

#ifndef _UdpClientSystem_
    #define _UdpClientSystem_

    #include "ATcpClientSystem.hpp"
    #include "Serialize.hpp"
    #include "Services.hpp"
    #include <iostream>
    #include <string>
    #include <memory>
    #include <boost/thread/thread.hpp>
    #include <boost/asio.hpp>
    #include <boost/array.hpp>
    #include <boost/bind/bind.hpp>

    using boost::asio::ip::tcp;
    using namespace boost::placeholders;

    namespace rtype {
        class TcpClientSystem : public ATcpClientSystem
        {
        private:
            tcp::socket _socket;
            std::string _message;
            std::array<char, 1024> data_;
            const size_t _nullscene;
            std::queue<Serialize::Data> _queue;
            std::shared_ptr<Services::IService> _service;

            void onReceive(const boost::system::error_code& err, std::size_t size) {
                std::cout << "On Received" << std::endl;
                if (!err && err != boost::asio::error::eof && size > 0) {
                    Serialize::Data received_data = Serialize::deserialize<Serialize::Data>(std::string(this->data_.data(), size), size);
                    this->_queue.push(received_data);
                }
                if (err == boost::asio::error::eof) {
                    std::cout << "Server Closed" << std::endl;
                }
                if (err) {
                    std::cout << "Error: " << err.message() << std::endl;
                    return;
                }
                this->_socket.async_receive(boost::asio::buffer(this->data_),
                                            boost::bind(&TcpClientSystem::onReceive, this,
                                                        boost::asio::placeholders::error,
                                                        boost::asio::placeholders::bytes_transferred));
            };

            void handler_quit(const boost::system::error_code& /*error*/, std::size_t /*bytes_transferred*/) {
                std::cout << "Send quit to server" << std::endl;
                this->_socket.close();
            };

            void onConnect(const boost::system::error_code& err) {
                std::cout << "Conneted to server" << std::endl;
                if (!err) {
                    std::cout << "Connected to server" << std::endl;
                    this->start_receive();
                } else {
                    std::cerr << err.message() << std::endl;
                }
            };

        public:
            TcpClientSystem(boost::asio::io_context &ioc, std::string IpServer, int portServer, std::shared_ptr<Services::IService> services) : _socket(ioc), ATcpClientSystem("ClientSystem"), _nullscene(0), _service(services) {
                std::cout << "Client started" << std::endl;
                tcp::endpoint endpoint(boost::asio::ip::address::from_string(IpServer), portServer);
                _socket.async_connect(endpoint, boost::bind(&TcpClientSystem::onConnect, this, boost::asio::placeholders::error));
            };

            ~TcpClientSystem() {};


            const std::string &getName() const { return (""); };
            bool isGameStillPlaying() { return true; };
            const size_t &getCurrentScene() const { return this->_nullscene; };

            void start_receive() {
                std::cout << "start receive" << std::endl;
                boost::asio::async_read(this->_socket, boost::asio::buffer(this->data_), boost::asio::transfer_at_least(1), boost::bind(&TcpClientSystem::onReceive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
            };

            void sendDataToServer(Serialize::Data info) {
                std::string data = Serialize::serialize<Serialize::Data>(info);
                this->_socket.async_send(boost::asio::buffer(data), boost::bind(&TcpClientSystem::handler_quit, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
            };

            void init() {
                this->_socket.open(tcp::v4());
                this->sendDataToServer(Serialize::createData<Serialize::Data>(Services::Command::CONNECTED, {}));
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
                this->_socket.close();
            };
            std::pair<size_t, size_t> getWindowWSize() const {
                return std::make_pair(0, 0);
            }
        };
    }

#endif /* !_TcpClientSystem_ */