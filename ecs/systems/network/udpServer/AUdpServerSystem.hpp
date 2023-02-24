/*
** EPITECH PROJECT, 2023
** AUdpClientSystem
** File description:
** AUdpClientSystem
*/

#ifndef _AUdpServerSystem_
    #define _AUdpServerSystem_
    #include <string>
    #include "ISystem.hpp"

    namespace rtype {
        /**
         * @brief Abstract for all UdpServerSystem
         *
         */
        class AUdpServerSystem : public ISystem {
            public:
                /**
                 * @brief Construct a new AClientSystem (used by the children class)
                 *
                 * @param libraryName the client library name
                 */
                AUdpServerSystem(const std::string &libraryName) : _libraryName(libraryName) {}

                /**
                 * @brief Get the Library Name object
                 *
                 * @return the library name as a const std::string&
                 */
                const std::string &getLibraryName() const
                {
                    return _libraryName;
                }

            protected:
                /**
                 * @brief the library name
                 *
                 */
                std::string _libraryName;
        };
    }

#endif /* _ATcpClientSystem_ */