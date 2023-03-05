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

    using namespace boost::asio;
    using namespace boost::placeholders;
    using namespace boost::asio::ip;

    namespace rtype {
        class UdpClientSystem : public AUdpClientSystem {
            public:
                UdpClientSystem(boost::asio::io_context &ioc, std::string ip, std::string port, std::shared_ptr<Services::IService> services);
                
                void start_receive();

                void send_data(size_t s_id,std::string text);

                const std::string &getName() const;

                bool isGameStillPlaying();

                const size_t &getCurrentScene() const;

                void init();

                void update(std::shared_ptr<IScene> &scene);

                void destroy();

                std::pair<size_t, size_t> getWindowWSize() const;

                ~UdpClientSystem() {};

            private:
                void handler_quit(const boost::system::error_code & /*error*/, std::size_t /*bytes_transferred*/);

                void handler_received(const boost::system::error_code &error, std::size_t size);

                void handler_send(const boost::system::error_code & /*error*/, std::size_t /*bytes_transferred*/);

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
