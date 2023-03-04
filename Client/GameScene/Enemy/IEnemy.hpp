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
                virtual bool handle(const int64_t &time, ComponentManager &componentManager, EntityManager &entityManager) = 0;

                /**
                 * @brief Get the id of the enemy
                 * 
                 * @return the component manager as a ComponentManager& 
                 */
                virtual entity_t &getId() = 0;

                /**
                 * @brief Get the pos of the enemy
                 * 
                 * @return the position of the enemy as a std::pair<size_t, size_t> 
                 */
                virtual std::pair<size_t, size_t> getPos() = 0;
        };
    }

#endif /* !_IEnemy_ */