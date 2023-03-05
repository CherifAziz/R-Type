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

                /**
                 * @brief Constructor of the service class
                 *
                 */
                Service();
                void callService(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene);
                void callService(Serialize::Data &data, rtype::IScene &scene);

                /**
                 * @brief Destructor of the service class
                 *
                 */
                ~Service();

            private:
                void Connected(Serialize::Data &data, rtype::IScene &scene);
                void Disconnect(Serialize::Data &data, rtype::IScene &scene);
                void Move(Serialize::Data &data, rtype::IScene &scene);
                void Shoot(Serialize::Data &data, rtype::IScene &scene);
                void NewPlayer(Serialize::Data &data, rtype::IScene &scene);
                void PlayerDisconnected(Serialize::Data &data, rtype::IScene &scene);
                void MovePlayer(Serialize::Data &data, rtype::IScene &scene);
                void ShootPlayer(Serialize::Data &data, rtype::IScene &scene);
                std::vector<std::function<void(Serialize::Data&, rtype::IScene&)>> _commands;
        };

    };

#endif /* !SERVICES_HPP_ */
