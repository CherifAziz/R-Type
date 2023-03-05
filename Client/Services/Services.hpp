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
                entity_t callService(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene);
                entity_t callService(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene);
                ~Service();

            private:
                entity_t Connected(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene);
                entity_t Disconnect(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene);
                entity_t Move(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene);
                entity_t Shoot(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene);
                entity_t NewPlayer(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene);
                entity_t createEnemy(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene);
                entity_t PlayerDisconnected(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene);
                entity_t MovePlayer(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene);
                entity_t ShootPlayer(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene);
                entity_t NewEnemy(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene);
                entity_t createPlayer(rtype::ComponentManager &Components, rtype::EntityManager &Entities, boost::uuids::uuid uid);
                entity_t createEnemy(rtype::ComponentManager &Components, rtype::EntityManager &Entities, Serialize::Data &data);
                std::vector<std::function<entity_t(Serialize::Data&, rtype::UdpClientSystem &, rtype::IScene&)>> _commands;
        };

    };

#endif /* !SERVICES_HPP_ */
