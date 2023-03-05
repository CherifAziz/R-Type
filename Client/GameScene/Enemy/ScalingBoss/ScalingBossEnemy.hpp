/*
** EPITECH PROJECT, 2023
** ScalingBossEnemy.hpp
** File description:
** ScalingBossEnemy
*/

#ifndef _ScalingBossEnemy_
    #define _ScalingBossEnemy_

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
        class ScalingBossEnemy : public AEnemy {
            public:
                /**
                 * @brief Construct a new BossEnemy
                 *
                 */
                ScalingBossEnemy(ComponentManager &componentManager, EntityManager &entityManager);
                
                /**
                 * @brief Destroy the BossEnemy class
                 *
                 */
                ~ScalingBossEnemy();

                /**
                 * @brief Move the enemy
                 *
                 */
                void move(Sprite &player_sprite, Sprite &sprite, Movement &movement);

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

            protected:

                size_t _lastHp;
        };
    }

#endif /* !_ScalingBossEnemy_ */