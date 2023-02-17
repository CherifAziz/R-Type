/*
** EPITECH PROJECT, 2023
** services
** File description:
** services
*/

#ifndef SERVICES_HPP_
    #define SERVICES_HPP_

    #include "Serialize.hpp"
    #include "ComponentManager.hpp"
    #include "EntityManager.hpp"
    #include <vector>
    #include <functional>

    namespace Serialize {
        struct Data;
    }

    namespace Services {
        enum Type : int {
            NOTIF = 0,
            COMMAND
        };

        enum Command {
            CONNECTED = 0,
            DISCONNECTED,
            MOVE,
            SHOOT,
        };

        enum Notification {
            NEW_PLAYER = 0,
            PLAYER_MOVE,
            PLAYER_SHOOT,
        };

        class Service {
            public:
                Service() {
                    this->_commands.push_back(std::bind(&Service::Connected, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
                    this->_commands.push_back(std::bind(&Service::Disconnect, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
                    this->_commands.push_back(std::bind(&Service::Move, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
                    this->_commands.push_back(std::bind(&Service::Shoot, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
                    this->_notifs.push_back(std::bind(&Service::NewPlayer, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
                    this->_notifs.push_back(std::bind(&Service::PlayerMove, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
                };

                void callService(Serialize::Data &data, rtype::ComponentManager &Components, rtype::EntityManager &Entities) {
                    switch (data.type) {
                        case Services::Type::COMMAND:
                            this->_commands[data.s_id](data, Components, Entities);
                            break;
                        case Services::Type::NOTIF:
                            this->_notifs[data.s_id](data, Components, Entities);
                            break;
                        default:
                            break;
                    }
                };

                ~Service() {};

            private:
                void Connected(Serialize::Data &data, rtype::ComponentManager &Components, rtype::EntityManager &Entities) {
                    std::cout << "connected" << std::endl;
                };

                void Disconnect(Serialize::Data &data, rtype::ComponentManager &Components, rtype::EntityManager &Entities) {
                    std::cout << "disconnect" << std::endl;
                };

                void Move(Serialize::Data &data, rtype::ComponentManager &Components, rtype::EntityManager &Entities) {
                    std::cout << "move" << std::endl;
                };

                void Shoot(Serialize::Data &data, rtype::ComponentManager &Components, rtype::EntityManager &Entities) {
                    std::cout << "shoot" << std::endl;
                };

                void NewPlayer(Serialize::Data &data, rtype::ComponentManager &Components, rtype::EntityManager &Entities) {
                    std::cout << "new player" << std::endl;
                };

                void PlayerMove(Serialize::Data &data, rtype::ComponentManager &Components, rtype::EntityManager &Entities) {
                    std::cout << "player move" << std::endl;
                };

                std::vector<std::function<void(Serialize::Data&, rtype::ComponentManager&, rtype::EntityManager&)>> _notifs;
                std::vector<std::function<void(Serialize::Data&, rtype::ComponentManager&, rtype::EntityManager&)>> _commands;
        };
    }

#endif /* !SERVICES_HPP_ */
