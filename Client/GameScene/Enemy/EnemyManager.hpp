/*
** EPITECH PROJECT, 2023
** EnemyManager.hpp
** File description:
** Enemy manager
*/

#ifndef _EnemyManager_
    #define _EnemyManager_

    #include "AScene.hpp"

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
            STUPID,
            FLY,
            BOSS
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
            protected:
                std::vector<> _entity;
        };
    }

#endif /* !_EnemyManager_ */