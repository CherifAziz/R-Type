/*
** EPITECH PROJECT, 2023
** GameValues
** File description:
** GameValues
*/

#ifndef GameValues
    #define GameValues

    #include <map>

    #include "GameScene.hpp"

    #define PLAYER_X_DEFAULT_SPRITE 133
    #define PLAYER_X_UP_SPRITE 167
    #define PLAYER_X_UP_PRESSED_SPRITE 201
    #define PLAYER_X_DOWN_SPRITE 99
    #define PLAYER_X_DOWN_PRESSED_SPRITE 65

    #define PLAYER_SPRITE_WIDTH     33
    #define PLAYER_SPRITE_HEIGHT    18

    #define ENEMY_REACH 30

    typedef struct frame {
        unsigned int x;
        unsigned int y;
        unsigned int width;
        unsigned int height;
    } frame_t;

    static const std::map<rtype::GameScene::BulletLoadState, std::pair<struct frame, struct frame>> bullet_frames = {
        {rtype::GameScene::BulletLoadState::LITTLE, {{249, 90, 16, 4}, {249, 90, 16, 4}}},
        {rtype::GameScene::BulletLoadState::CHARGED, {{232, 103, 16, 12}, {249, 105, 16, 8}}},
        {rtype::GameScene::BulletLoadState::BIG_CHARGE, {{200, 121, 32, 10}, {233, 120, 35, 12}}},
        {rtype::GameScene::BulletLoadState::SUPER_CHARGE, {{168, 137, 48, 12}, {217, 136, 48, 14}}},
        {rtype::GameScene::BulletLoadState::MEGA_CHARGE, {{136, 154, 64, 14}, {201, 154, 64, 14}}},
        {rtype::GameScene::BulletLoadState::BEBOU_CHARGE, {{106, 171, 78, 14}, {185, 170, 80, 16}}}
    };

#endif /* !GameValues */
