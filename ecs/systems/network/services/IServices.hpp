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

    namespace rtype {
        class UdpClient;
    };

    using namespace boost::asio::ip;
    using namespace rtype;

    namespace Services {
        enum Type : int {
            NOTIF = 0,
            COMMAND
        };

        enum Command : int {
            CONNECTED = 0,
            DISCONNECTED,
            MOVE,
            SHOOT,
        };

        enum Notification : int {
            NEW_PLAYER = 0,
            PLAYER_MOVE,
            PLAYER_SHOOT,
        };

        class IService {
            public:
                virtual void callService(std::map<udp::endpoint, std::unique_ptr<rtype::UdpClient>> &clients, Serialize::Data &data, rtype::ComponentManager &Components, rtype::EntityManager &Entities) = 0;
                virtual ~IService() = default;
        };

    }

#endif /* !ISERVICES_HPP_ */
