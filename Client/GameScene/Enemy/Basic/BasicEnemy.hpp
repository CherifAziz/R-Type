/*
** EPITECH PROJECT, 2023
** BasicEnemy.hpp
** File description:
** BasicEnemy
*/

#ifndef _BasicEnemy_
    #define _BasicEnemy_

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
         * @brief The BasicEnemy class
         *
         */
        class BasicEnemy : public IEnemy {
            public:
                /**
                 * @brief Construct a new BasicEnemy
                 *
                 */
                BasicEnemy(ComponentManager &componentManager, EntityManager &entityManager);
                
                /**
                 * @brief Destroy the BasicEnemy class
                 *
                 */
                ~BasicEnemy();

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
                bool destroy(Sprite &sprite, Animation &animation, entity_t enemy_id, ComponentManager &componentManager, EntityManager &entityManager);

                /**
                 * @brief handle the enemy
                 *
                 */
                void handle(const int64_t &time, ComponentManager &componentManager, EntityManager &entityManager);

            protected:
                /**
                 * @brief the hp point of the BasicEnemy
                 * 
                 */
                size_t _hp;
        };
    }

#endif /* !_BasicEnemy_ */