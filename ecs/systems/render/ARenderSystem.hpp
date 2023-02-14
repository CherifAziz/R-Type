/*
** EPITECH PROJECT, 2023
** ARenderSystem
** File description:
** ARenderSystem
*/

#ifndef _ARenderSystem_
    #define _ARenderSystem_

    #include "ISystem.hpp"

    namespace rtype {
        /**
         * @brief Abstract for all Render System
         * 
         */
        class ARenderSystem : public ISystem {
            public:
                /**
                 * @brief Construct a new ARenderSystem (used by the children class)
                 * 
                 * @param libraryName the rendering library name
                 */
                ARenderSystem(const std::string &libraryName) : _libraryName(libraryName) {}

                /**
                 * @brief Get the Library name or the Game name of the object
                 * 
                 * @return the name as a const std::string& 
                 */
                const std::string &getName() const
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

#endif /* !_ARenderSystem_ */