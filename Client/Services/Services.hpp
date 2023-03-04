/*
** EPITECH PROJECT, 2023
** Services.hpp
** File description:
** Services
*/

#ifndef SERVICES_HPP_
    #define SERVICES_HPP_

    #include "UdpClientSystem.hpp"

    using namespace rtype;

    namespace Services {
        class Service : public IService {
            public:
                Service();
                void callService(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene);
                void callService(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene);
                ~Service();

            private:
                void Connected(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene);
                void Disconnect(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene);
                void Move(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene);
                void Shoot(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene);
                void NewPlayer(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene);
                void createEnemy(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene);
                void PlayerDisconnected(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene);
                void MovePlayer(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene);
                void ShootPlayer(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene);
                void NewEnemy(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene);
                void createPlayer(rtype::ComponentManager &Components, rtype::EntityManager &Entities, boost::uuids::uuid uid);
                void createEnemy(rtype::ComponentManager &Components, rtype::EntityManager &Entities, Serialize::Data &data);
                std::vector<std::function<void(Serialize::Data&, rtype::UdpClientSystem &, rtype::IScene&)>> _commands;
        };

    };

#endif /* !SERVICES_HPP_ */
