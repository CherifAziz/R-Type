/*
** EPITECH PROJECT, 2023
** FlyEnemy.hpp
** File description:
** FlyEnemy
*/

#ifndef _FlyEnemy_
    #define _FlyEnemy_

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
         * @brief The FlyEnemy class
         *
         */
        class FlyEnemy : public IEnemy {
            public:
                /**
                 * @brief Construct a new flyenemy
                 *
                 */
                FlyEnemy(ComponentManager &componentManager, EntityManager &entityManager);
                
                /**
                 * @brief Destroy the flyenemy class
                 *
                 */
                ~FlyEnemy();

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
                bool destroy(ComponentManager &componentManager, EntityManager &entityManager);

                /**
                 * @brief handle the enemy
                 *
                 */
                void handle(const int64_t &time, ComponentManager &componentManager, EntityManager &entityManager);

            protected:
                /**
                 * @brief the hp point of the fly enemy
                 * 
                 */
                size_t _hp;
        };
    }

#endif /* !_FlyEnemy_ */