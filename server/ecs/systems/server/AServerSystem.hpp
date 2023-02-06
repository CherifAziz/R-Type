/*
** EPITECH PROJECT, 2023
** AServerSystem
** File description:
** AServerSystem
*/

#ifndef _AServerSystem_
    #define _AServerSystem_

    #include <string>
    #include "ISystem.hpp"

    namespace rtype {
        class AServerSystem : public ISystem {
            public:
            /**
             * @brief Construct a new ARenderSystem (used by the children class)
             *
             * @param libraryName the rendering library name
             */
            AServerSystem(const std::string &libraryName) : _libraryName(libraryName) {}

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

#endif /* !_AServerSystem_ */
