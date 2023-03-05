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

    #include "GameValues.hpp"

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

                bool isAlreadyAnEnemyHere(size_t x, size_t y, ComponentManager &componentManager, EntityManager &entityManager, const std::string &enemy);

                const size_t &getHp() const;

                void setHp(size_t hp);

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
