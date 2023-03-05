/*
** EPITECH PROJECT, 2023
** ChildBossEnemy.hpp
** File description:
** ChildBossEnemy
*/

#ifndef _ChildBossEnemy_
    #define _ChildBossEnemy_

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
         * @brief The ChildBossEnemy class
         *
         */
        class ChildBossEnemy : public AEnemy {
            public:
                /**
                 * @brief Construct a new ChildBossEnemy
                 *
                 */
                ChildBossEnemy(ComponentManager &componentManager, EntityManager &entityManager);
                
                /**
                 * @brief Destroy the ChildBossEnemy class
                 *
                 */
                ~ChildBossEnemy();

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
                 */
                bool handle(const int64_t &time, ComponentManager &componentManager, EntityManager &entityManager);
        };
    }

#endif /* !_ChildBossEnemy_ */