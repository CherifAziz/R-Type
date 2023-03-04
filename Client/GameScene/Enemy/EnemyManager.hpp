/*
** EPITECH PROJECT, 2023
** EnemyManager.hpp
** File description:
** Enemy manager
*/

#ifndef _EnemyManager_
    #define _EnemyManager_

    #include "IEnemy.hpp"

    #include "EnemyValues.hpp"

    #include <unordered_map>

    namespace rtype {
        /**
         * @brief The Enemy manager to handle life, damage and more else
         *
         */
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
                std::shared_ptr<IEnemy> createEnemy(std::string &enemy, ComponentManager &componentManager, EntityManager &entityManager);

                /**
                 * @brief handle all enemies comportement
                 *
                 */
                void handleEnemies(const int64_t &time, ComponentManager &componentManager, EntityManager &entityManager);

                const size_t &getEnemyHp(const entity_t &entity);

                void setEnemyHp(const entity_t &entity, const size_t &hp);

            protected:
                /**
                 * @brief List of all instancied enemy
                 *
                 */
                std::vector<std::shared_ptr<IEnemy>> _enemies;
        };
    }

#endif /* !_EnemyManager_ */