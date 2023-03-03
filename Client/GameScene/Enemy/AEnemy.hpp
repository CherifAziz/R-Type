/*
** EPITECH PROJECT, 2023
** AEnemy.hpp
** File description:
** Abstract class Enemy manager
*/

#ifndef _AEnemy_
    #define _AEnemy_

    #include "IEnemy.hpp"
    #include "ComponentManager.hpp"
    #include "EntityManager.hpp"

    namespace rtype {
        /**
         * @brief Abstract class for RType Enemy Manager
         * 
         */
        class AEnemy : public IEnemy
        {
            public:
                /**
                 * @brief Get the id of the enemy
                 * 
                 * @return the component manager as a ComponentManager& 
                 */
                entity_t &getId() { return _id; }

            protected:
               /**
                 * @brief the hp point of the enemy
                 * 
                 */
                size_t _hp;

                /**
                 * @brief the id of the enemy
                 * 
                 */
                entity_t _id;
        };
    }

#endif /* !_AEnemy_ */