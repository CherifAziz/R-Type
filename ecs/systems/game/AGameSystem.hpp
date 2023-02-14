/*
** EPITECH PROJECT, 2023
** AGameSystem
** File description:
** AGameSystem
*/


#ifndef _AGameSystem_
    #define _AGameSystem_

    #include "ISystem.hpp"
    #include "IScene.hpp"

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
                 * @param defaultScene the default scene index
                 *
                 */
                AGameSystem(const std::string &name, const size_t &defaultScene = 0) : _name(name), _currentScene(defaultScene) {}

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

                /**
                 * @brief the scenes
                 * 
                 */
                std::vector<std::shared_ptr<IScene>> _scenes;

                /**
                 * @brief the current scene in the vector
                 * 
                 */
                size_t _currentScene;
        };
    }

#endif /* !_AGameSystem_ */