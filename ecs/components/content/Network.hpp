/*
** EPITECH PROJECT, 2023
** Network.hpp
** File description:
** Network
*/

#ifndef NETWORK_HPP_
    #define NETWORK_HPP_

    #include <queue>
    #include <optional>
    #include "Serialize.hpp"
    #include <boost/uuid/uuid.hpp>
    #include <boost/uuid/uuid_generators.hpp>
    #include <boost/uuid/uuid_io.hpp>
    #include <boost/lexical_cast.hpp>

    namespace rtype {
        class Network {
            public:
                Network(boost::uuids::uuid uid = boost::uuids::random_generator()()) : _uuid(uid) {};

                ~Network() {};

                boost::uuids::uuid getUUID() const { return _uuid; };

                void setUUID(boost::uuids::uuid uid) {
                    this->_uuid = uid;
                };

                std::optional<Serialize::Data> getCommands() {
                    if (!this->_queue.empty()) {
                        std::cout << "getCommands" << std::endl;
                        Serialize::Data data = this->_queue.front();
                        this->_queue.pop();
                        return data;
                    }
                    return std::nullopt;
                };

                bool addToQueue(Serialize::Data data) {
                    try {
                        this->_queue.push(data);
                        return true;
                    } catch (std::exception &e) {
                        std::cout << "error addToQueue => " << e.what() << std::endl;
                        return false;
                    }
                }

            private:
                boost::uuids::uuid _uuid;
                std::queue<Serialize::Data> _queue;
        };
    }

#endif /* !NETWORK_HPP_ */
