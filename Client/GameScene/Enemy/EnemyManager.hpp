/*
** EPITECH PROJECT, 2023
** EnemyManager.hpp
** File description:
** Enemy manager
*/

#ifndef _EnemyManager_
    #define _EnemyManager_

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
         * @brief The Enemy manager to handle life, damage and more else
         *
         */
        enum EnemyType: int {
            BASIC = 0,
            FLY,
            BOSS,
            STUPID
        };

        class EnemyManager {
            public:
                /**
                 * @brief Construct a new vector of enemy
                 *
                 */
                EnemyManager();
                
                /**
                 * @brief Destroy the enemy's vector
                 *
                 */
                ~EnemyManager();

                /**
                 * @brief create a new enemy and adding it to the list of enemy
                 *
                 */
                std::shared_ptr<IEnemy> createEnemy(EnemyType type, ComponentManager &componentManager, EntityManager &entityManager);

                /**
                 * @brief handle all enemies comportement
                 *
                 */
                void enemiesHandle(const int64_t &time, ComponentManager &componentManager, EntityManager &entityManager);

            protected:
                std::vector<std::shared_ptr<IEnemy>> _enemies;
        };
    }

#endif /* !_EnemyManager_ */