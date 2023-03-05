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
        /**
         * @brief The VesselEnemy class
         *
         */
        class VesselEnemy : public AEnemy {
            public:

                /**
                 * @brief Constructor of the Vessel Enemy
                 *
                 */
                VesselEnemy(ComponentManager &componentManager, EntityManager &entityManager);
                
                /**
                 * @brief Destructor of the Vessel Enemy
                 *
                 */
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
                 * @return Return true if the enemy has been destroyed 
                 */
                bool handle(const int64_t &time, ComponentManager &componentManager, EntityManager &entityManager);
        };
    }

#endif /* !_VesselEnemy_ */