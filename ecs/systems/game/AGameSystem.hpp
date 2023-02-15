/*
** EPITECH PROJECT, 2023
** AGameSystem
** File description:
** AGameSystem
*/


#ifndef _AGameSystem_
    #define _AGameSystem_

    #include "ISystem.hpp"

    namespace rtype {
        /**
         * @brief Abstract for all GameSystem
         * 
         */
        class AGameSystem : public ISystem {
            public:
                /**
                 * @brief Construct a new AGameSystem object (used by the children class)
                 * 
                 * @param name the input game name
                 *
                 */
                AGameSystem(const std::string &name) : _name(name) {}

                /**
                 * @brief Get the Library name or the Game name of the object
                 * 
                 * @return the name as a const std::string& 
                 */
                const std::string &getName() const
                {
                    return _name;
                }

            protected:
                /**
                 * @brief The Game Name
                 * 
                 */
                std::string _name;
        };
    }

#endif /* !_AGameSystem_ */