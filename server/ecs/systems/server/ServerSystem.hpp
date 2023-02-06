/*
** EPITECH PROJECT, 2023
** ServerSystem
** File description:
** ServerSystem
*/

#ifndef _ServerSystem_
    #define _ServerSystem_

    #include "AServerSystem.hpp"
    #include <iostream>
    #include <string>
    #include <memory>
    #include <boost/asio.hpp>
    #include <boost/bind/bind.hpp>
    #include <boost/shared_ptr.hpp>
    #include <boost/enable_shared_from_this.hpp>
    #include <boost/archive/binary_oarchive.hpp>
    #include <boost/archive/binary_iarchive.hpp>
    #include <boost/serialization/serialization.hpp>

    using boost::asio::ip::tcp;
    using namespace boost::placeholders;

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
        class ClientServer : public std::enable_shared_from_this<ClientServer> {
            public:
                ClientServer(boost::asio::io_context& io_context): _socket(io_context) {};
                tcp::socket &getSocket() { return this->_socket; };

                void start() {
                    std::cout << "client started" << std::endl;
                    Serialize::Data info = { 0, "Connected to Server" };
                    std::string data = Serialize::serialize<Serialize::Data>(info);
                    boost::asio::async_write(this->_socket, boost::asio::buffer(data), boost::bind(&ClientServer::onWrite, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
                    this->start_read();
                };

                void start_read() {
                    boost::asio::async_read(this->_socket, boost::asio::buffer(this->data_), boost::asio::transfer_at_least(1), boost::bind(&ClientServer::onRead, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
                };

                ~ClientServer() { this->_socket.close(); };

            private:
                void onRead(const boost::system::error_code& err, size_t size) {
                        if (err && err != boost::asio::error::eof) {
                            std::cerr << err.message() << std::endl;
                            return;
                        }
                        if (err == boost::asio::error::eof)
                            return;
                        Serialize::Data received_data = Serialize::deserialize<Serialize::Data>(std::string(this->data_.data(), size), size);
                        std::cout << "Received data from client: " << received_data.size << received_data._data << std::endl;
                        boost::asio::async_read(this->_socket, boost::asio::buffer(this->data_), boost::asio::transfer_at_least(1), boost::bind(&ClientServer::onRead, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
                };

                void onWrite(const boost::system::error_code& err, size_t size) {
                    std::cout << "message sent : " << size  << std::endl;
                    if (err)
                        std::cout << err.what() << std::endl;
                };

                tcp::socket _socket;
                std::array<char, 1024> data_;
        };

        class ServerSystem : public AServerSystem {
            public:
                ServerSystem(boost::asio::io_context& ioc, int port) : AServerSystem("ServerSystem"), _acceptor(ioc, tcp::endpoint(tcp::v4(), port)), _io_context(ioc) {
                    std::cout << "ServerSystem created" << std::endl;
                    this->start_accept();
                    this->_io_context.run();
                };

                void start_accept() {
                    std::cout << "start accept" << std::endl;
                    this->_clients.push_back(std::make_shared<ClientServer>(this->_io_context));
                    this->_acceptor.async_accept(this->_clients[this->_clients.size() - 1]->getSocket(),
                        boost::bind(&ServerSystem::handle_accept, this, this->_clients[this->_clients.size() - 1], boost::asio::placeholders::error));
                };

                void handle_accept(std::shared_ptr<ClientServer> client, const boost::system::error_code& err) {
                    std::cout << "client connect to server" << std::endl;
                    if (!err) {
                        client->start();
                        this->_clients.push_back(std::make_shared<ClientServer>(this->_io_context));
                        this->_acceptor.async_accept(this->_clients[this->_clients.size() - 1]->getSocket(),
                                boost::bind(&ServerSystem::handle_accept, this, this->_clients[this->_clients.size() - 1], boost::asio::placeholders::error));
                    } else {
                        std::cerr << "err: " << err.message() << std::endl;
                        client.reset();
                        this->_clients.pop_back();
                    }
                };

                ~ServerSystem() {};

                void init() {};
                void update(ComponentManager &/*componentManager*/, EntityManager &/*entityManager*/) {};
                void destroy() {};

            private:
                tcp::acceptor _acceptor;
                boost::asio::io_context &_io_context;
                std::vector<std::shared_ptr<ClientServer> > _clients;
        };
    }

#endif /* !_ServerSystem_ */