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
                ClientServer(boost::asio::io_context& io_context);

                tcp::socket &getSocket();

                void start();

                void start_read();

                ~ClientServer();

            private:
                void onRead(const boost::system::error_code& err, size_t size);

                void onWrite(const boost::system::error_code& err, size_t size);

                tcp::socket _socket;
                std::array<char, 1024> data_;
        };

        class TcpServerSystem : public ATcpServerSystem {
            public:
                TcpServerSystem(boost::asio::io_context& ioc, int port);

                ~TcpServerSystem();

                void start_accept();

                void handle_accept(std::shared_ptr<ClientServer> client, const boost::system::error_code& err);

                const std::string &getName() const;
                bool isGameStillPlaying();
                const size_t &getCurrentScene() const;
                void init() {};
                void update(std::shared_ptr<IScene> &/*scene*/) {};
                void destroy() {};
                /**
                 * @brief check the connection status
                 * 
                 * @return true if it's connected to the server, false otherwise
                 */
                bool isConnected()
                {
                    return _storage->isConnected();
                }

                std::pair<size_t, size_t> getWindowWSize() const;
                
            private:
                std::shared_ptr<Storage> _storage;
                tcp::acceptor _acceptor;
                boost::asio::io_context &_io_context;
                std::vector<std::shared_ptr<ClientServer> > _clients;
                std::shared_ptr<Storage> _storage;
        };
    }

#endif /* !_TcpServerSystem_ */