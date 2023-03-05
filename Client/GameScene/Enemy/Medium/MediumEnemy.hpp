/*
** EPITECH PROJECT, 2023
** MediumEnemy
** File description:
** MediumEnemy
*/

#ifndef _MediumEnemy_
    #define _MediumEnemy_

    #include "AEnemy.hpp"

    #include "Sprite.hpp"
    #include "Movement.hpp"
    #include "Animation.hpp"

    namespace rtype {
        /**
         * @brief The MediumEnemy class
         *
         */
        class MediumEnemy : public AEnemy {
            public:

                /**
                 * @brief Constructor of the Medium Enemy class
                 *
                 */
                MediumEnemy(ComponentManager &componentManager, EntityManager &entityManager);

                /**
                 * @brief Destructor of the Medium Enemy class
                 *
                 */
                ~MediumEnemy();

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

#endif /* !_MediumEnemy_ */