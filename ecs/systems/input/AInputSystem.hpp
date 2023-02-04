/*
** EPITECH PROJECT, 2023
** AInputSystem
** File description:
** AInputSystem
*/

#ifndef _AInputSystem_
    #define _AInputSystem_

    #include "ISystem.hpp"

    namespace rtype {
        /**
         * @brief Abstract for all InputSystem
         * 
         */
        class AInputSystem : public ISystem {
            public:
                /**
                 * @brief Construct a new AInputSystem (used by the children class)
                 * 
                 * @param libraryName the input library name
                 */
                AInputSystem(const std::string &libraryName) : _libraryName(libraryName) {}

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

#endif /* !_AInputSystem_ */