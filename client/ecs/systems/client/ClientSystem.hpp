/*
** EPITECH PROJECT, 2023
** ClientSystem
** File description:
** ClientSystem
*/

#ifndef _ClientSystem_
    #define _ClientSystem_

    #include "AClientSystem.hpp"
    #include <iostream>
    #include <string>
    #include <boost/asio.hpp>
    #include <boost/array.hpp>
    #include <boost/bind/bind.hpp>
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
    }

    namespace rtype {
        class ClientSystem : public AClientSystem
        {
        private:
            tcp::socket _socket;
            std::string _message;
            std::array<char, 1024> data_;

            void onReceive(const boost::system::error_code& err, std::size_t size) {
                 std::cout << "On Received" << std::endl;
                if (err && err != boost::asio::error::eof) {
                    std::cerr << err.message() << std::endl;
                    return;
                }
                if (err == boost::asio::error::eof)
                    return;
                Serialize::Data received_data = Serialize::deserialize<Serialize::Data>(std::string(this->data_.data(), size), size);
                std::cout << "Received data: " << received_data.size << received_data._data << std::endl;
                boost::asio::async_read(this->_socket, boost::asio::buffer(this->data_), boost::asio::transfer_at_least(1) , boost::bind(&ClientSystem::onReceive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
            };

            void onSent(const boost::system::error_code& err) {
                std::cout << "On Sent" << std::endl;
                if (err) {
                    std::cerr << err.message() << std::endl;
                    return;
                }
            };

            void onConnect(const boost::system::error_code& err) {
                if (!err) {
                    std::cout << "Connected to server" << std::endl;
                    this->start_receive();
                }
            };

        public:
            ClientSystem(boost::asio::io_context &ioc, std::string IpServer, int portServer = 3333) : _socket(ioc), AClientSystem("Network") {
                tcp::endpoint endpoint(boost::asio::ip::address::from_string(IpServer), portServer);
                _socket.async_connect(endpoint, boost::bind(&ClientSystem::onConnect, this, boost::asio::placeholders::error));
            };
            ~ClientSystem();

            void start_receive() {
                std::cout << "start receive" << std::endl;
                boost::asio::async_read(this->_socket, boost::asio::buffer(this->data_), boost::asio::transfer_at_least(1) , boost::bind(&ClientSystem::onReceive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
            };

            void sendDataToServer(std::string data) {
                Serialize::Data info = { 43, data };
                std::string data = Serialize::serialize<Serialize::Data>(info);
                boost::asio::async_write(this->_socket, boost::asio::buffer(data), boost::bind(&ClientSystem::onSent, this, boost::asio::placeholders::error));
            };
        };
    }

#endif /* !_ClientSystem_ */