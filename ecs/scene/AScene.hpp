/*
** EPITECH PROJECT, 2023
** AScene
** File description:
** AScene
*/

#ifndef _AScene_
    #define _AScene_

    #include "IScene.hpp"

    #include "ComponentManager.hpp"
    #include "EntityManager.hpp"

    namespace rtype {
        /**
         * @brief the Abstract for Scene class
         * 
         */
        class AScene : public IScene {
            public:
                /**
                 * @brief Get the Component Manager object
                 * 
                 * @return the component manager as a ComponentManager& 
                 */
                ComponentManager &getComponentManager() { return _componentManager; }

                /**
                 * @brief Get the Entity Manager object
                 * 
                 * @return the entity manager as a EntityManager& 
                 */
                EntityManager &getEntityManager() { return _entityManager; }

            protected:
                /**
                 * @brief the component manager
                 * 
                 */
                ComponentManager _componentManager;

                /**
                 * @brief the entity manager
                 * 
                 */
                EntityManager _entityManager;
        };
    }

#endif /* !_AScene_ */
