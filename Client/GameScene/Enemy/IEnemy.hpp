/*
** EPITECH PROJECT, 2023
** IEnemy.hpp
** File description:
** Interface Enemy manager
*/

#ifndef ICoreDef
    #define ICoreDef

    #include "ComponentManager.hpp"
    #include "EntityManager.hpp"

    namespace rtype {
        /**
         * @brief the Interface Enemy Class
         *
         */
        class IEnemy
        {
            public:
                /**
                 * @brief Destroy the IEnemy object
                 *
                 */
                virtual ~IEnemy() = default;

                /**
                 * @brief handle every enemy
                 *
                 */
                virtual void handle();

                /**
                 * @brief handle movement of the enemy
                 *
                 */
                virtual void move();

                /**
                 * @brief destroy the current alive enemy
                 *
                 * @return true if the enemy is dead
                 */
                virtual bool destroy(ComponentManager &componentManager, EntityManager &entityManager);
        };
    }

#endif /* !IEnemy */