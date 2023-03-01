/*
** EPITECH PROJECT, 2023
** BossEnemy.hpp
** File description:
** BossEnemy
*/

#ifndef _BossEnemy_
    #define _BossEnemy_

    #include "AScene.hpp"
    #include "IEnemy.hpp"

    #include "Sprite.hpp"
    #include "Action.hpp"
    #include "Animation.hpp"
    #include "Movement.hpp"
    #include "Sound.hpp"
    #include "Network.hpp"

    namespace rtype {
        /**
         * @brief The BossEnemy class
         *
         */
        class BossEnemy : public IEnemy{
            public:
                /**
                 * @brief Construct a new BossEnemy
                 *
                 */
                BossEnemy(ComponentManager &componentManager, EntityManager &entityManager);
                
                /**
                 * @brief Destroy the BossEnemy class
                 *
                 */
                ~BossEnemy();

                /**
                 * @brief Move the enemy
                 *
                 */
                void move(Sprite &sprite, Movement &movement);

                /**
                 * @brief Destroy the enemy
                 *
                 * @return true if the enemy is dead
                 */
                bool destroy(ComponentManager &componentManager, EntityManager &entityManager);

                /**
                 * @brief handle the enemy
                 *
                 */
                void handle(const int64_t &time, ComponentManager &componentManager, EntityManager &entityManager);

            protected:
                /**
                 * @brief the hp point of the BossEnemy
                 * 
                 */
                size_t _hp;
        };
    }

#endif /* !_BossEnemy_ */