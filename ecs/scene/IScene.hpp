/*
** EPITECH PROJECT, 2023
** IScene
** File description:
** IScene
*/

#ifndef _IScene_
    #define _IScene_

    #include "ComponentManager.hpp"
    #include "EntityManager.hpp"

    namespace rtype {
        /**
         * @brief the Interface for Scene class
         * 
         */
        class IScene {
            public:
                /**
                 * @brief Destroy the IScene object
                 * 
                 */
                virtual ~IScene() = default;

                /**
                 * @brief Get the Component Manager object
                 * 
                 * @return the component manager as a ComponentManager& 
                 */
                virtual ComponentManager &getComponentManager() = 0;

                /**
                 * @brief Get the Entity Manager object
                 * 
                 * @return the entity manager as a EntityManager& 
                 */
                virtual EntityManager &getEntityManager() = 0;

                /**
                 * @brief init the Scene (must be override)
                 * 
                 */
                virtual void init() = 0;

                /**
                 * @brief update the scene components and entities (must be override)
                 * 
                 * @param time the current time that has been elapsed
                 */
                virtual void update(const int64_t &time) = 0;

                /**
                 * @brief destroy the scene (must be override)
                 * 
                 */
                virtual void destroy() = 0;

                /**
                 * @brief check if the game is still playing
                 * 
                 * @return true if the game is still playing, false otherwise
                 */
                virtual const bool &isGameStillPlaying() const = 0;

            protected:
        };
    }

#endif /* !_IScene_ */
