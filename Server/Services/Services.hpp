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
                void callService(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene);
                void callService(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene);
                ~Service();

            private:
                void Connected(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene);
                void Disconnect(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene);
                void Move(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene);
                void Shoot(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene);
                void NewPlayer(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene);
                void PlayerMove(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene);
                void NewEnemy(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene);
                void Useless(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene);
                std::vector<std::function<void(udp::endpoint&, rtype::ClientManager&, Serialize::Data&, rtype::IScene&)>> _commands;
        };

    };

#endif /* !SERVICES_HPP_ */
