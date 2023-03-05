/*
** EPITECH PROJECT, 2023
** EnemyValues
** File description:
** EnemyValues
*/

#ifndef EnemyValues
    #define EnemyValues

    #include <vector>
    #include <string>
    #include <unordered_map>

    namespace rtype {
        static const std::vector<std::string> ENEMIES = {
            "basicEnemy",
            "mediumEnemy",
            "vesselEnemy",
            "flyEnemy",
            "bossEnemy",
            "scalingBossEnemy",
            "childBossEnemy",
        };

        const std::unordered_map<std::string, size_t> ENEMY_LIMITER = {
            {"basicEnemy", 5},
            {"mediumEnemy", 3},
            {"vesselEnemy", 3},
            {"flyEnemy", 2},
            {"bossEnemy", 1},
            {"scalingBossEnemy", 1},
            {"childBossEnemy", 1}
        };

        const std::unordered_map<std::string, size_t> ENEMY_SCORE = {
            {"basicEnemy", 10},
            {"mediumEnemy", 15},
            {"vesselEnemy", 25},
            {"flyEnemy", 20},
            {"bossEnemy", 50},
            {"scalingBossEnemy", 50},
            {"childBossEnemy", 50}
        };

        const std::unordered_map<std::string, size_t> ENEMY_LIFE = {
            {"basicEnemy", 1},
            {"mediumEnemy", 5},
            {"vesselEnemy", 15},
            {"flyEnemy", 10},
            {"bossEnemy", 100},
            {"scalingBossEnemy", 100},
            {"childBossEnemy", 200}
        };
    }

#endif /* !EnemyValues */
