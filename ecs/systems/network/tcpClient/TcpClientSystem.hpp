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

            void onReceive(const boost::system::error_code& err, std::size_t size);
            void onSent(const boost::system::error_code& err);

            void onConnect(const boost::system::error_code& err);

        public:
            TcpClientSystem(boost::asio::io_context &ioc, std::string IpServer, int portServer);

            ~TcpClientSystem();


            const std::string &getName() const;
            
            bool isGameStillPlaying();

            const size_t &getCurrentScene() const;

            void start_receive();

            void sendDataToServer(std::string data);

            void init() {};

            void update(std::shared_ptr<IScene> &/*scene*/) {};

            void destroy();

            std::pair<size_t, size_t> getWindowWSize() const;
        };
    }

#endif /* !_TcpClientSystem_ */