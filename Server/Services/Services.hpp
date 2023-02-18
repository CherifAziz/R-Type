/*
** EPITECH PROJECT, 2023
** Services.hpp
** File description:
** Services
*/

#ifndef SERVICES_HPP_
    #define SERVICES_HPP_

    #include "AServices.hpp"

    using namespace rtype;

    namespace Services {
        class Service : public AService {
            public:
                Service();
                ~Service();

            private:
                void Connected(std::map<udp::endpoint, std::unique_ptr<UdpClient>> &clients, Serialize::Data &data, rtype::ComponentManager &Components, rtype::EntityManager &Entities);
                void Disconnect(std::map<udp::endpoint, std::unique_ptr<UdpClient>> &clients, Serialize::Data &data, rtype::ComponentManager &Components, rtype::EntityManager &Entities);
                void Move(std::map<udp::endpoint, std::unique_ptr<UdpClient>> &clients, Serialize::Data &data, rtype::ComponentManager &Components, rtype::EntityManager &Entities);
                void Shoot(std::map<udp::endpoint, std::unique_ptr<UdpClient>> &clients, Serialize::Data &data, rtype::ComponentManager &Components, rtype::EntityManager &Entities);
                void NewPlayer(std::map<udp::endpoint, std::unique_ptr<UdpClient>> &clients, Serialize::Data &data, rtype::ComponentManager &Components, rtype::EntityManager &Entities);
                void PlayerMove(std::map<udp::endpoint, std::unique_ptr<UdpClient>> &clients, Serialize::Data &data, rtype::ComponentManager &Components, rtype::EntityManager &Entities);
        };

    };

#endif /* !SERVICES_HPP_ */
