/*
** EPITECH PROJECT, 2023
** IEnemy.hpp
** File description:
** Interface Enemy manager
*/

#ifndef _IEnemy_
    #define _IEnemy_

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
                virtual void handle(const int64_t &time, ComponentManager &componentManager, EntityManager &entityManager) = 0;
        };
    }

#endif /* !_IEnemy_ */