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

    #include "ACore.hpp"
    #include "ISystem.hpp"

    #include "Storage.hpp"

    namespace rtype {
        /**
         * @brief the Core class
         * 
         */
        class Core : public ACore
        {
            public:
                /**
                 * @brief Construct a new Core object
                 * 
                 */
                Core();

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
                 * @brief check if the game is still running
                 * 
                 * @return true if the game is still running, false otherwise
                 */
                const bool &isGameRunning() const;

                /**
                 * @brief Get the Component Manager object
                 * 
                 * @return the component manager as a ComponentManager& 
                 */
                ComponentManager &getComponentManager() const;

                /**
                 * @brief Get the Entity Manager object
                 * 
                 * @return the entity manager as a EntityManager& 
                 */
                EntityManager &getEntityManager() const;

                /**
                 * @brief the systems
                 * 
                 */
                std::vector<std::shared_ptr<ISystem>> _systems;
        };
    }

#endif /* !CoreGuard */
