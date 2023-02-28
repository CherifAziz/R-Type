/*
** EPITECH PROJECT, 2023
** BasicEnemy
** File description:
** BasicEnemy
*/

#include "GameScene.hpp"
#include "GameValues.hpp"

#include "Collision.hpp"

namespace rtype {
    bool GameScene::isAlreadyAnEnemyHere(size_t x, size_t y)
    {
        std::vector<std::shared_ptr<Entity>> basicEnemies = _entityManager.getEntitiesFromFamily("basicEnemy");

        for (auto &basicEnemy : basicEnemies) {
            Sprite &sprite = _componentManager.get<Sprite>(basicEnemy->getId());

            if ((int)x > sprite.getX() - ENEMY_REACH && (int)x < sprite.getX() + ENEMY_REACH)
                return true;
            else if ((int)y > sprite.getY() - ENEMY_REACH && (int)y < sprite.getY() + ENEMY_REACH)
                return true;
        }
        return false;
    }

    // bool GameScene::isAlreadyAnFlyEnemyHere(size_t x, size_t y)
    // {
    //     std::vector<std::shared_ptr<Entity>> flyEnemies = _entityManager.getEntitiesFromFamily("fly");

    //     for (auto &flyEnemy : flyEnemies) {
    //         Sprite &sprite = _componentManager.get<Sprite>(flyEnemy->getId());

    //         if ((int)x > sprite.getX() - ENEMY_REACH && (int)x < sprite.getX() + ENEMY_REACH)
    //             return true;
    //         else if ((int)y > sprite.getY() - ENEMY_REACH && (int)y < sprite.getY() + ENEMY_REACH)
    //             return true;
    //     }
    //     return false;
    // }

    void GameScene::spawnBasicEnemy()
    {
        size_t x = 1920 + rand() % 100;
        size_t y = rand() % (900 - ENEMY_REACH);

        while (isAlreadyAnEnemyHere(x, y)) {
            x = 1920 + rand() % 500;
            y = rand() % (900 - ENEMY_REACH);
        }
        entity_t enemy = _entityManager.spawnEntity("basicEnemy")->getId();
        Sprite sprite("assets/basicEnemy.gif", x, y, 4);
        Animation animation(20, 30, 5, 7, 8, 1, 12, 0, 500);
        Movement movement(-5, 0);
        Collision collision({"player"});

        _componentManager.put<Sprite>(sprite, enemy);
        _componentManager.put<Animation>(animation, enemy);
        _componentManager.put<Movement>(movement, enemy);
        _componentManager.put<Collision>(collision, enemy);
    }


    void GameScene::moveBasicEnemy(Sprite &sprite, Movement &movement)
    {
        sprite.setPosition(sprite.getX() + movement.getXDirection(), sprite.getY() + movement.getYDirection());
    }

    bool GameScene::destroyBasicEnemy(Sprite &sprite, Animation &animation, entity_t enemy_id)
    {
        (void)enemy_id;
        if ((int)(sprite.getX() + animation.getRectWidth()) < 0) {
            _componentManager.killEntity(enemy_id);
            _entityManager.killEntity(enemy_id);
            return true;
        }
        return false;
    }

    void GameScene::handleBasicEnemy(const int64_t &time)
    {
        std::vector<std::shared_ptr<Entity>> basicEnemies = _entityManager.getEntitiesFromFamily("basicEnemy");
        std::shared_ptr<ComponentMap<Movement>> movementMap = _componentManager.getComponents<Movement>();
        std::shared_ptr<ComponentMap<Sprite>> spriteMap = _componentManager.getComponents<Sprite>();
        std::shared_ptr<ComponentMap<Animation>> animationMap = _componentManager.getComponents<Animation>();

        for (auto &basicEnemy : basicEnemies) {
            if (destroyBasicEnemy(spriteMap->get(basicEnemy->getId()), animationMap->get(basicEnemy->getId()), basicEnemy->getId()))
                return handleBasicEnemy(time);
            if (movementMap->contains(basicEnemy->getId()) && spriteMap->contains(basicEnemy->getId()))
                moveBasicEnemy(spriteMap->get(basicEnemy->getId()), movementMap->get(basicEnemy->getId()));
        }
        if (basicEnemies.size() < 5 && time % 20 == 0)
            spawnBasicEnemy();
    }

    // void GameScene::moveBoss(Sprite &sprite, Movement &movement)
    // {
    //     sprite.setPosition(sprite.getX() + movement.getXDirection(), sprite.getY() + movement.getYDirection());
    // }

    // bool GameScene::BossDeath(Sprite &sprite, Animation &animation, entity_t enemy_id)
    // {
    //     (void)enemy_id;
    //     if ((int)(sprite.getX() + animation.getRectWidth()) < 0) {
    //         _componentManager.killEntity(enemy_id);
    //         _entityManager.killEntity(enemy_id);
    //         return true;
    //     }
    //     return false;
    // }

    // void GameScene::handleBoss(const int64_t &time)
    // {
    //     std::vector<std::shared_ptr<Entity>> boss = _entityManager.getEntitiesFromFamily("boss");
    //     std::shared_ptr<ComponentMap<Movement>> movementMap = _componentManager.getComponents<Movement>();
    //     std::shared_ptr<ComponentMap<Sprite>> spriteMap = _componentManager.getComponents<Sprite>();
    //     std::shared_ptr<ComponentMap<Animation>> animationMap = _componentManager.getComponents<Animation>();

    //     for (auto &boss : boss) {
    //         if (BossDeath(spriteMap->get(boss->getId()), animationMap->get(boss->getId()), boss->getId()))
    //             return handleBoss(time);
    //         if (movementMap->contains(boss->getId()) && spriteMap->contains(boss->getId()))
    //             moveBoss(spriteMap->get(boss->getId()), movementMap->get(boss->getId()));
    //     }
    // }

    // void GameScene::spawnBoss()
    // {
    //     size_t x = 800;
    //     size_t y = 450;
    //     // size_t x = 1920 + rand() % 100;
    //     // size_t y = rand() % (900 - ENEMY_REACH);

    //     // while (isAlreadyAnEnemyHere(x, y)) {
    //     //     x = 1920 + rand() % 500;
    //     //     y = rand() % (900 - ENEMY_REACH);
    //     // }
    //     entity_t enemy = _entityManager.spawnEntity("boss")->getId();
    //     Sprite sprite("assets/boss1.gif", x, y, 4);
    //     Animation animation(255, 142, 0, 0, 2, 4, 5, 3, 2000);
    //     Movement movement(0, 1);
    //     Collision collision({"player"});

    //     _componentManager.put<Sprite>(sprite, enemy);
    //     _componentManager.put<Animation>(animation, enemy);
    //     _componentManager.put<Movement>(movement, enemy);
    //     _componentManager.put<Collision>(collision, enemy);
    // }

    // void GameScene::moveFlyEnemy(Sprite &sprite, Movement &movement)
    // {
    //     sprite.setPosition(sprite.getX() + movement.getXDirection(), sprite.getY() + movement.getYDirection());
    // }

    // bool GameScene::destroyFlyEnemy(Sprite &sprite, Animation &animation, entity_t enemy_id)
    // {
    //     (void)enemy_id;
    //     if ((int)(sprite.getX() + animation.getRectWidth()) < 0) {
    //         _componentManager.killEntity(enemy_id);
    //         _entityManager.killEntity(enemy_id);
    //         return true;
    //     }
    //     return false;
    // }

    // void GameScene::spawnFlyEnemy()
    // {
    //     // size_t x = 1800;
    //     // size_t y = 500;
    //     size_t x = 1920 + rand() % 100;
    //     size_t y = rand() % (900 - ENEMY_REACH);

    //     while (isAlreadyAnFlyEnemyHere(x, y)) {
    //         x = 1920 + rand() % 500;
    //         y = rand() % (900 - ENEMY_REACH);
    //     }
    //     entity_t enemy = _entityManager.spawnEntity("fly")->getId();
    //     Sprite sprite("assets/flyenemy.gif", x, y, 3);
    //     Animation animation(61, 46, 4, 3, 6, 1, 6, 0, 2000);
    //     Movement movement(-2, 0);
    //     Collision collision({"player"});

    //     _componentManager.put<Sprite>(sprite, enemy);
    //     _componentManager.put<Animation>(animation, enemy);
    //     _componentManager.put<Movement>(movement, enemy);
    //     _componentManager.put<Collision>(collision, enemy);
    // }

    // void GameScene::handleFlyEnemy(const int64_t &time)
    // {
    //     std::vector<std::shared_ptr<Entity>> flyEnemies = _entityManager.getEntitiesFromFamily("fly");
    //     std::shared_ptr<ComponentMap<Movement>> movementMap = _componentManager.getComponents<Movement>();
    //     std::shared_ptr<ComponentMap<Sprite>> spriteMap = _componentManager.getComponents<Sprite>();
    //     std::shared_ptr<ComponentMap<Animation>> animationMap = _componentManager.getComponents<Animation>();

    //     for (auto &flyEnemy : flyEnemies) {
    //         if (destroyFlyEnemy(spriteMap->get(flyEnemy->getId()), animationMap->get(flyEnemy->getId()), flyEnemy->getId()))
    //             return handleFlyEnemy(time);
    //         if (movementMap->contains(flyEnemy->getId()) && spriteMap->contains(flyEnemy->getId()))
    //             moveFlyEnemy(spriteMap->get(flyEnemy->getId()), movementMap->get(flyEnemy->getId()));
    //     }
    //     if (flyEnemies.size() < 5 && time % 20 == 0) {
    //         spawnFlyEnemy();
    //     }
    // }
}
