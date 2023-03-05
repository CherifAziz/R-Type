/*
** EPITECH PROJECT, 2023
** AUdpClientSystem
** File description:
** AUdpClientSystem
*/

#ifndef _AUdpClientSystem_
    #define _AUdpClientSystem_
    #include <string>
    #include "ISystem.hpp"

    namespace rtype {
        /**
         * @brief Abstract for all UdpServerSystem
         *
         */
        class AUdpClientSystem : public ISystem {
            public:
                /**
                 * @brief Construct a new AClientSystem (used by the children class)
                 *
                 * @param libraryName the client library name
                 */
                AUdpClientSystem(const std::string &libraryName);
                /**
                 * @brief Get the Library Name object
                 *
                 * @return the library name as a const std::string&
                 */
                const std::string &getLibraryName() const;

            protected:
                /**
                 * @brief the library name
                 *
                 */
                std::string _libraryName;
        };
    }

#endif /* _ATcpClientSystem_ */