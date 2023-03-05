/*
** EPITECH PROJECT, 2023
** BossEnemy.hpp
** File description:
** BossEnemy
*/

#ifndef _BossEnemy_
    #define _BossEnemy_

    #include "AScene.hpp"
    #include "AEnemy.hpp"

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
        class BossEnemy : public AEnemy {
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
                bool destroy(Sprite &sprite, Animation &animation, ComponentManager &componentManager, EntityManager &entityManager);

                /**
                 * @brief handle the enemy
                 *
                 * @return Return true if the enemy has been destroyed 
                 */
                bool handle(const int64_t &time, ComponentManager &componentManager, EntityManager &entityManager);
        };
    }

#endif /* !_BossEnemy_ */