/*
** EPITECH PROJECT, 2023
** Network.hpp
** File description:
** Network
*/

#ifndef NETWORK_HPP_
    #define NETWORK_HPP_

    #include <stack>
    #include <optional>
    #include "Serialize.hpp"
    #include <boost/uuid/uuid.hpp>
    #include <boost/uuid/uuid_generators.hpp>
    #include <boost/uuid/uuid_io.hpp>
    #include <boost/lexical_cast.hpp>

    namespace rtype {
        class Network {
            public:
                Network(boost::uuids::uuid uid = boost::uuids::random_generator()()) : _uuid(uid) {
                    std::cout << "New Network Component" << std::endl;
                };
                ~Network() {};
                boost::uuids::uuid getUUID() const { return _uuid; };

                void setUUID(boost::uuids::uuid uid) { this->_uuid = uid; };

                std::optional<Serialize::Data> getCommands() {
                    std::cout << _uuid << " GetCommand => " << this->_queue.size() << std::endl;
                    // if (!this->_queue.empty()) {
                    //     Serialize::Data data = this->_queue.front();
                        // this->_queue.pop();
                    //     return data;
                    // }
                    return std::nullopt;
                };

                bool addToQueue(Serialize::Data data) {
                    try {
                        this->_queue.push(data);
                        std::cout << _uuid << " add to Queue => " << this->_queue.size() << std::endl;
                        return true;
                    } catch (std::exception &e) {
                        std::cout << "error addToQueue => " << e.what() << std::endl;
                        return false;
                    }
                }

            private:
                boost::uuids::uuid _uuid;
                std::stack<Serialize::Data> _queue;
        };
    }

#endif /* !NETWORK_HPP_ */
