/*
** EPITECH PROJECT, 2023
** FlyEnemy.hpp
** File description:
** FlyEnemy
*/

#ifndef _FlyEnemy_
    #define _FlyEnemy_

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
         * @brief The FlyEnemy class
         *
         */
        class FlyEnemy : public AEnemy {
            public:
                /**
                 * @brief Construct a new flyenemy
                 *
                 */
                FlyEnemy(ComponentManager &componentManager, EntityManager &entityManager, const size_t &windowWidth, const size_t &windowHeight);
                
                /**
                 * @brief Destroy the flyenemy class
                 *
                 */
                ~FlyEnemy();

                /**
                 * @brief Move the enemy
                 *
                 */
                void move(Sprite &sprite, Movement &movement, Animation &animation, const size_t &windowWidth, const size_t &windowHeight);

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
                bool handle(const int64_t &time, ComponentManager &componentManager, EntityManager &entityManager, const size_t &windowWidth, const size_t &windowHeight);
        };
    }

#endif /* !_FlyEnemy_ */