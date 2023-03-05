/*
** EPITECH PROJECT, 2023
** EnemyManager.hpp
** File description:
** Enemy manager
*/

#ifndef _EnemyManager_
    #define _EnemyManager_

    #include "IEnemy.hpp"

    #include <unordered_map>

    namespace rtype {
        /**
         * @brief EnemyEnum to handle the type of the enemy
         *
         */
        enum EnemyType: int {
            BASIC = 0,
            FLY,
            BOSS,
            MEDIUM,
            VESSEL
        };

        /**
         * @brief An unordered map which is handling the limit of every enemy type displayable on player's screen
         *
         */
        const std::unordered_map<EnemyType, size_t> enemyLimiter = {
            {EnemyType::BASIC, 5},
            {EnemyType::FLY, 3},
            {EnemyType::BOSS, 1},
            {EnemyType::MEDIUM, 3},
            {EnemyType::VESSEL, 4}
        };

        const std::unordered_map<EnemyType, std::string> enemyTranslator = {
            {EnemyType::BASIC, "basicEnemy"},
            {EnemyType::FLY, "flyEnemy"},
            {EnemyType::BOSS, "boss"},
            {EnemyType::MEDIUM, "mediumEnemy"},
            {EnemyType::VESSEL, "vesselEnemy"}
        };

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
                std::shared_ptr<IEnemy> createEnemy(EnemyType type, ComponentManager &componentManager, EntityManager &entityManager);

                /**
                 * @brief handle all enemies comportement
                 *
                 */
                void handleEnemies(const int64_t &time, ComponentManager &componentManager, EntityManager &entityManager);

            protected:
                /**
                 * @brief List of all instancied enemy
                 *
                 */
                std::vector<std::shared_ptr<IEnemy>> _enemies;
        };
    }

#endif /* !_EnemyManager_ */