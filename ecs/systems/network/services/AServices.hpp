/*
** EPITECH PROJECT, 2023
** services
** File description:
** services
*/

#ifndef ASERVICES_HPP_
    #define ASERVICES_HPP_

    #include "IServices.hpp"
    #include <vector>
    #include <functional>

    namespace Services {
        class AService : public IService {
            public:
                void callService(std::map<udp::endpoint, std::unique_ptr<UdpClient>> &clients, Serialize::Data &data, rtype::ComponentManager &Components, rtype::EntityManager &Entities) {
                    switch (data.type) {
                        case Services::Type::COMMAND:
                            this->_commands[data.s_id](clients, data, Components, Entities);
                            break;
                        case Services::Type::NOTIF:
                            this->_notifs[data.s_id](clients, data, Components, Entities);
                            break;
                        default:
                            break;
                    }
                };

            protected:
                std::vector<std::function<void(std::map<udp::endpoint, std::unique_ptr<UdpClient>> &, Serialize::Data&, rtype::ComponentManager&, rtype::EntityManager&)>> _notifs;
                std::vector<std::function<void(std::map<udp::endpoint, std::unique_ptr<UdpClient>> &, Serialize::Data&, rtype::ComponentManager&, rtype::EntityManager&)>> _commands;
        };
    };

#endif /* !ASERVICES_HPP_ */
