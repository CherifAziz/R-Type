/*
** EPITECH PROJECT, 2023
** Services.hpp
** File description:
** Services
*/

#ifndef SERVICES_HPP_
    #define SERVICES_HPP_

    #include "IServices.hpp"

    using namespace rtype;

    namespace Services {
        class Service : public IService {
            public:
                Service();
                entity_t callService(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene);
                entity_t callService(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene);
                ~Service();

            private:
                entity_t Connected(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene);
                entity_t Disconnect(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene);
                entity_t Move(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene);
                entity_t Shoot(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene);
                entity_t NewPlayer(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene);
                entity_t PlayerMove(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene);
                entity_t NewEnemy(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene);
                entity_t Useless(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene);
                std::vector<std::function<entity_t(udp::endpoint&, rtype::ClientManager&, Serialize::Data&, rtype::IScene&)>> _commands;
        };

    };

#endif /* !SERVICES_HPP_ */
