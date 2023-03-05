/*
** EPITECH PROJECT, 2023
** BasicEnemy.hpp
** File description:
** BasicEnemy
*/

#ifndef _BasicEnemy_
    #define _BasicEnemy_

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
         * @brief The BasicEnemy class
         *
         */
        class BasicEnemy : public AEnemy {
            public:
                /**
                 * @brief Construct a new BasicEnemy
                 *
                 */
                BasicEnemy(ComponentManager &componentManager, EntityManager &entityManager, const size_t &windowWidth, const size_t &windowHeight);
                
                /**
                 * @brief Destroy the BasicEnemy class
                 *
                 */
                ~BasicEnemy();

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
                 * @return Return true if the enemy has been destroyed 
                 */
                bool handle(const int64_t &time, ComponentManager &componentManager, EntityManager &entityManager, const size_t &windowWidth, const size_t &windowHeight);
        };
    }

#endif /* !_BasicEnemy_ */