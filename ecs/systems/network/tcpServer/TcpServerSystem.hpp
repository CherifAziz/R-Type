/*
** EPITECH PROJECT, 2023
** ServerSystem
** File description:
** ServerSystem
*/

#ifndef _TcpServerSystem_
    #define _TcpServerSystem_

    #include "ATcpServerSystem.hpp"
    #include "Serialize.hpp"
    #include "Storage.hpp"
    #include <iostream>
    #include <string>
    #include <memory>
    #include <thread>
    #include <boost/thread.hpp>
    #include <boost/asio.hpp>
    #include <boost/bind/bind.hpp>
    #include <boost/shared_ptr.hpp>
    #include <boost/enable_shared_from_this.hpp>

    using boost::asio::ip::tcp;
    using namespace boost::placeholders;

    namespace rtype {
        class ClientServer : public std::enable_shared_from_this<ClientServer> {
            public:
                ClientServer(boost::asio::io_context& io_context): _socket(io_context) {};
                tcp::socket &getSocket() { return this->_socket; };

                void start() {
                    std::cout << "client started" << std::endl;
                    Serialize::Data info = Serialize::createData<Serialize::Data>(0, "");
                    std::string data = Serialize::serialize<Serialize::Data>(info);
                    boost::asio::async_write(this->_socket, boost::asio::buffer(data), boost::bind(&ClientServer::onWrite, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
                    sleep(2);
                    boost::asio::async_write(this->_socket, boost::asio::buffer(data), boost::bind(&ClientServer::onWrite, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
                    this->start_read();
                };

                void start_read() {
                    boost::asio::async_read(this->_socket, boost::asio::buffer(this->data_), boost::asio::transfer_at_least(1), boost::bind(&ClientServer::onRead, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
                };

                ~ClientServer() {
                    this->_socket.close();
                };

            private:
                void onRead(const boost::system::error_code& err, size_t size) {
                        if (err && err != boost::asio::error::eof) {
                            std::cerr << err.message() << std::endl;
                            return;
                        }
                        if (err == boost::asio::error::eof)
                            return;
                        Serialize::Data received_data = Serialize::deserialize<Serialize::Data>(std::string(this->data_.data(), size), size);
                        boost::asio::async_read(this->_socket, boost::asio::buffer(this->data_), boost::asio::transfer_at_least(1), boost::bind(&ClientServer::onRead, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
                };

                void onWrite(const boost::system::error_code& err, size_t size) {
                    std::cout << "message sent : " << size  << std::endl;
                    if (err)
                        std::cout << err.message() << std::endl;
                };

                tcp::socket _socket;
                std::array<char, 1024> data_;
        };

        class TcpServerSystem : public ATcpServerSystem {
            public:
                TcpServerSystem(boost::asio::io_context& ioc, int port) : ATcpServerSystem("TcpServer"), _acceptor(ioc, tcp::endpoint(tcp::v4(), port)), _io_context(ioc), _storage(Storage::getStorage()) {
                    std::cout << "ServerSystem created" << std::endl;
                    this->start_accept();
                };
                ~TcpServerSystem() {};

                void start_accept() {
                    std::cout << "start accept" << std::endl;
                    this->_clients.push_back(std::make_shared<ClientServer>(this->_io_context));
                    this->_acceptor.async_accept(this->_clients[this->_clients.size() - 1]->getSocket(),
                        boost::bind(&TcpServerSystem::handle_accept, this, this->_clients[this->_clients.size() - 1], boost::asio::placeholders::error));
                };

                void handle_accept(std::shared_ptr<ClientServer> client, const boost::system::error_code& err) {
                    std::cout << "client connect to server" << std::endl;
                    if (!err) {
                        client->start();
                        this->_clients.push_back(std::make_shared<ClientServer>(this->_io_context));
                        this->_acceptor.async_accept(this->_clients[this->_clients.size() - 1]->getSocket(),
                                boost::bind(&TcpServerSystem::handle_accept, this, this->_clients[this->_clients.size() - 1], boost::asio::placeholders::error));
                    } else {
                        std::cerr << "err: " << err.message() << std::endl;
                        client.reset();
                        this->_clients.pop_back();
                    }
                };


                const std::string &getName() const { return (""); };
                bool isGameStillPlaying() { return _storage->isStillPlaying(); };
                const size_t &getCurrentScene() const { return 0; };
                void init() {};
                void update(std::shared_ptr<IScene> &/*scene*/) {};
                void destroy() {};

                std::pair<size_t, size_t> getWindowWSize() const {
                    return std::make_pair(0, 0);
                }

            private:
                std::shared_ptr<Storage> _storage;
                tcp::acceptor _acceptor;
                boost::asio::io_context &_io_context;
                std::vector<std::shared_ptr<ClientServer> > _clients;
                std::shared_ptr<Storage> _storage;
        };
    }

#endif /* !_TcpServerSystem_ */