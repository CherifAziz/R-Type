/*
** EPITECH PROJECT, 2023
** VesselEnemy
** File description:
** VesselEnemy
*/

#ifndef _VesselEnemy_
    #define _VesselEnemy_

    #include "AEnemy.hpp"

    #include "Sprite.hpp"
    #include "Movement.hpp"
    #include "Animation.hpp"

    namespace rtype {
        class VesselEnemy : public AEnemy {
            public:
                VesselEnemy(ComponentManager &componentManager, EntityManager &entityManager);
                ~VesselEnemy();

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

#endif /* !_VesselEnemy_ */