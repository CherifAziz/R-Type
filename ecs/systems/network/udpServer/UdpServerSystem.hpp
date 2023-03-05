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
    #include "IServices.hpp"
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
                UdpClient(udp::endpoint endpoint, udp::socket &socket);

                void sendDataToClient(Serialize::Data data);

                udp::endpoint &getEndpoint();

                boost::uuids::uuid &getUuid();

                void setUuid(boost::uuids::uuid uuid);

                entity_t &getEntity();

                void setEntity(entity_t entity);

                void handler_send(const boost::system::error_code &error, std::size_t bytes_transferred);

                void addToListOfCommands(Serialize::Data &data);

                std::optional<Serialize::Data> getCommand();

                ~UdpClient();

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
                ClientManager();
                ~ClientManager();

                void addClient(udp::endpoint endpoint,  udp::socket &socket);

                void removeClient(udp::endpoint endpoint);

                std::optional<UdpClient * const> getClient(udp::endpoint endpoint);

                void sendToEachClient(Serialize::Data data);

                std::map<udp::endpoint, std::unique_ptr<UdpClient>> &getClients();

            private:
                std::map<udp::endpoint, std::unique_ptr<UdpClient>> _clients;
        };

        class UdpServerSystem : public AUdpServerSystem {
            public:
                UdpServerSystem(boost::asio::io_service &io_service, int port, std::shared_ptr<Services::IService> services);

                void start_receive();

                void send_data(int s_id, std::string text, boost::asio::ip::udp::endpoint endpoint);

                void init() {};

                const std::string &getName() const;

                bool isGameStillPlaying();

                const size_t &getCurrentScene() const;

                void update(std::shared_ptr<IScene> &scene);

                void destroy() {};

                std::pair<size_t, size_t> getWindowWSize() const;

                ~UdpServerSystem();

            protected:
            private:
                void handler_received(const boost::system::error_code &error, std::size_t size);

                void handler_send(const boost::system::error_code &/*error*/, std::size_t /*bytes_transferred*/);

                udp::socket _socker;
                udp::endpoint _remote_endpoint;
                std::array<char, 1024> _data;
                std::shared_ptr<Services::IService> _service;
                ClientManager _clients;
                const std::string _nullstring;
                const size_t _nullscene;
        };
    }

#endif /* !UDPSERVERSYSTEM_HPP_ */
