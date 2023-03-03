/*
** EPITECH PROJECT, 2023
** StupidEnemy
** File description:
** StupidEnemy
*/

#ifndef _StupidEnemy_
    #define _StupidEnemy_

    #include "AEnemy.hpp"

    #include "Sprite.hpp"
    #include "Movement.hpp"
    #include "Animation.hpp"

    namespace rtype {
        class StupidEnemy : public AEnemy {
            public:
                StupidEnemy(ComponentManager &componentManager, EntityManager &entityManager);
                ~StupidEnemy();

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

#endif /* !_StupidEnemy_ */