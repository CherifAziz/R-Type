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
                void callService(udp::endpoint &client, std::map<udp::endpoint, std::unique_ptr<UdpClient>> &clients, Serialize::Data &data, rtype::IScene &scene);
                void callService(Serialize::Data &data, rtype::IScene &scene);
                ~Service();

            private:
                void Connected(udp::endpoint &client, std::map<udp::endpoint, std::unique_ptr<UdpClient>> &clients, Serialize::Data &data, rtype::IScene &scene);
                void Disconnect(udp::endpoint &client, std::map<udp::endpoint, std::unique_ptr<UdpClient>> &clients, Serialize::Data &data, rtype::IScene &scene);
                void Move(udp::endpoint &client, std::map<udp::endpoint, std::unique_ptr<UdpClient>> &clients, Serialize::Data &data, rtype::IScene &scene);
                void Shoot(udp::endpoint &client, std::map<udp::endpoint, std::unique_ptr<UdpClient>> &clients, Serialize::Data &data, rtype::IScene &scene);
                void NewPlayer(udp::endpoint &client, std::map<udp::endpoint, std::unique_ptr<UdpClient>> &clients, Serialize::Data &data, rtype::IScene &scene);
                void PlayerMove(udp::endpoint &client, std::map<udp::endpoint, std::unique_ptr<UdpClient>> &clients, Serialize::Data &data, rtype::IScene &scene);
                std::vector<std::function<void(udp::endpoint &, std::map<udp::endpoint, std::unique_ptr<UdpClient>> &, Serialize::Data&, rtype::IScene&)>> _commands;
        };

    };

#endif /* !SERVICES_HPP_ */
