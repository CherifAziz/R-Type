/*
** EPITECH PROJECT, 2023
** Core.hpp
** File description:
** Core structure
*/

#ifndef CoreGuard
    #define CoreGuard

    #include <SFML/Graphics.hpp>
    #include <vector>
    #include <memory>

    #include "ICore.hpp"
    #include "ISystem.hpp"
    #include "IScene.hpp"

    namespace rtype {
        /**
         * @brief the Core class
         * 
         */
        class Core : public ICore
        {
            public:
                /**
                 * @brief Construct a new Core object
                 * 
                 * @param defaultScene the default scene index
                 */
                Core(size_t defaultScene = 0);

                /**
                 * @brief Destroy the Core object
                 * 
                 */
                ~Core();

                /**
                 * @brief the game loop
                 * 
                 * @return int the game return value (84 if an error occured, 0 otherwise)
                 */
                int loopGame();

            private:
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

                /**
                 * @brief the systems
                 * 
                 */
                std::vector<std::shared_ptr<ISystem>> _systems;
        };
    }

#endif /* !CoreGuard */
