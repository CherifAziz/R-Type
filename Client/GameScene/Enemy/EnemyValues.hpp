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
            "bossEnemy"
        };

        const std::unordered_map<std::string, size_t> ENEMY_LIMITER = {
            {"basicEnemy", 5},
            {"mediumEnemy", 3},
            {"vesselEnemy", 4},
            {"flyEnemy", 3},
            {"bossEnemy", 1}
        };

        const std::unordered_map<std::string, size_t> ENEMY_SCORE = {
            {"basicEnemy", 10},
            {"mediumEnemy", 15},
            {"vesselEnemy", 25},
            {"flyEnemy", 20},
            {"bossEnemy", 50}
        };

        const std::unordered_map<std::string, size_t> ENEMY_LIFE = {
            {"basicEnemy", 1},
            {"mediumEnemy", 1},
            {"vesselEnemy", 1},
            {"flyEnemy", 1},
            {"bossEnemy", 100}
        };
    }

#endif /* !EnemyValues */
