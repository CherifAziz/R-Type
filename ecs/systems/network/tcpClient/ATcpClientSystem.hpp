/*
** EPITECH PROJECT, 2023
** AClientSystem
** File description:
** AClientSystem
*/

#ifndef _ATcpClientSystem_
    #define _ATcpClientSystem_
    #include <string>
    #include "ISystem.hpp"

    namespace rtype {
        /**
         * @brief Abstract for all ClientSystem
         *
         */
        class ATcpClientSystem : public ISystem {
            public:
                /**
                 * @brief Construct a new AClientSystem (used by the children class)
                 *
                 * @param libraryName the client library name
                 */
                ATcpClientSystem(const std::string &libraryName) {};

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