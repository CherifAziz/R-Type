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
    #include <iostream>
    #include <string>
    #include <memory>
    #include "Storage.hpp"
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
            std::shared_ptr<Storage> _storage;

            void onReceive(const boost::system::error_code& err, std::size_t size) {
                std::cout << "On Received" << std::endl;
                if (err && err != boost::asio::error::eof) {
                    std::cerr << err.message() << std::endl;
                    return;
                }
                if (err == boost::asio::error::eof)
                    return;
                Serialize::Data received_data = Serialize::deserialize<Serialize::Data>(std::string(this->data_.data(), size), size);
                boost::asio::async_read(this->_socket, boost::asio::buffer(this->data_), boost::asio::transfer_at_least(1), boost::bind(&TcpClientSystem::onReceive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
            };

            void onSent(const boost::system::error_code& err) {
                std::cout << "On Sent" << std::endl;
                if (err) {
                    std::cerr << err.message() << std::endl;
                    return;
                }
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
            TcpClientSystem(boost::asio::io_context &ioc, std::string IpServer, int portServer) : _socket(ioc), ATcpClientSystem("ClientSystem"), _storage(Storage::getStorage()) {
                std::cout << "Client started" << std::endl;
                tcp::endpoint endpoint(boost::asio::ip::address::from_string(IpServer), portServer);
                _socket.async_connect(endpoint, boost::bind(&TcpClientSystem::onConnect, this, boost::asio::placeholders::error));
            };

            ~TcpClientSystem() {};


            const std::string &getName() const { return (""); };
            bool isGameStillPlaying() { return _storage->isStillPlaying(); };
            const size_t &getCurrentScene() const { return 0; };
                /**
                 * @brief check the connection status
                 * 
                 * @return true if it's connected to the server, false otherwise
                 */
                bool isConnected()
                {
                    return _storage->isConnected();
                }

            void start_receive() {
                std::cout << "start receive" << std::endl;
                boost::asio::async_read(this->_socket, boost::asio::buffer(this->data_), boost::asio::transfer_at_least(1), boost::bind(&TcpClientSystem::onReceive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
            };

            void sendDataToServer(std::string data) {
                Serialize::Data info = { 43, data };
                std::string data_seria = Serialize::serialize<Serialize::Data>(info);
                boost::asio::async_write(this->_socket, boost::asio::buffer(data_seria), boost::bind(&TcpClientSystem::onSent, this, boost::asio::placeholders::error));
            };

            void init() {};
            void update(std::shared_ptr<IScene> &/*scene*/) {};
            void destroy() {
                this->_socket.close();
            };
            std::pair<size_t, size_t> getWindowWSize() const {
                return std::make_pair(0, 0);
            }
        };
    }

#endif /* !_TcpClientSystem_ */