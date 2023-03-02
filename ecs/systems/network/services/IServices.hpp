/*
** EPITECH PROJECT, 2023
** IServices.hpp
** File description:
** IServices
*/

#ifndef ISERVICES_HPP_
    #define ISERVICES_HPP_

    #include <map>
    #include <vector>
    #include <functional>
    #include <boost/asio.hpp>
    #include "Serialize.hpp"
    #include "ComponentManager.hpp"
    #include "EntityManager.hpp"
    #include "IScene.hpp"

    namespace rtype {
        class ClientManager;
        class UdpClientSystem;
        class TcpClientSystem;
    };

    using namespace boost::asio::ip;
    using namespace rtype;

    namespace Services {
        enum Command : int {
            CONNECTED = 0,
            DISCONNECTED,
            INPUT,
            NEW_PLAYER,
            PLAYER_DISCONNECTED,
            EVENT_PLAYER
        };

        class IService {
            public:
                virtual void callService(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene) = 0;
                virtual void callService(tcp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene) = 0;
                virtual void callService(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene) = 0;
                virtual void callService(Serialize::Data &data, rtype::TcpClientSystem &client, rtype::IScene &scene) = 0;
                virtual ~IService() = default;
        };

    }

#endif /* !ISERVICES_HPP_ */
