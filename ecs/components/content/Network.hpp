/*
** EPITECH PROJECT, 2023
** Network.hpp
** File description:
** Network
*/

#ifndef NETWORK_HPP_
    #define NETWORK_HPP_

    #include <boost/uuid/uuid.hpp>
    #include <boost/uuid/uuid_generators.hpp>
    #include <boost/uuid/uuid_io.hpp>
    #include <boost/lexical_cast.hpp>

    namespace rtype {

        /**
         * @brief the Network Class
         * 
         */
        class Network {
            public:

                /**
                 * @brief Constructor of the network class
                 * 
                 */
                Network(boost::uuids::uuid uid = boost::uuids::random_generator()()) : _uuid(uid) {};
                
                /**
                 * @brief destructor of the network class
                 * 
                 */
                ~Network() {};

                /**
                 * @brief Method to get the UUID of the network
                 * 
                 */
                boost::uuids::uuid getUUID() const { return _uuid; };

            private:

                /**
                 * @brief The UUID
                 * 
                 */
                boost::uuids::uuid _uuid;
        };
    }

#endif /* !NETWORK_HPP_ */
