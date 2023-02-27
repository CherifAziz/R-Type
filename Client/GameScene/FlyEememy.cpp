/*
** EPITECH PROJECT, 2023
** FlyEnemy
** File description:
** FlyEnemy
*/

#include "GameScene.hpp"
#include "GameValues.hpp"

#include "Collision.hpp"

namespace rtype {
    bool GameScene::isAlreadyFlyEnemyHere(size_t x, size_t y)
    {
        std::vector<std::shared_ptr<Entity>> flyEnemies = _entityManager.getEntitiesFromFamily("flyenemy");

        for (auto &flyEnemy : flyEnemies) {
            Sprite &sprite = _componentManager.get<Sprite>(flyEnemy->getId());

            if ((int)x > sprite.getX() - ENEMY_REACH && (int)x < sprite.getX() + ENEMY_REACH)
                return true;
            else if ((int)y > sprite.getY() - ENEMY_REACH && (int)y < sprite.getY() + ENEMY_REACH)
                return true;
        }
        return false;
    }

    void GameScene::spawnFlyEnemy()
    {
        size_t x = 1920 + rand() % 100;
        size_t y = rand() % (900 - ENEMY_REACH);

        while (isAlreadyFlyEnemyHere(x, y)) {
            x = 1920 + rand() % 500;
            y = rand() % (900 - ENEMY_REACH);
        }
        entity_t enemy = _entityManager.spawnEntity("flyenemy")->getId();
        Sprite sprite("assets/flyenemy.gif", x, y, 3);
        Animation animation(61, 46, 4, 3, 6, 1, 4, 0, 500);
        if (rand() % 2 == 0) {
            Movement movement(-3, -2);
            _componentManager.put<Movement>(movement, enemy);
        }
        else {
            Movement movement(-3, 2);
            _componentManager.put<Movement>(movement, enemy);
        }
        Collision collision({"player"});

        _componentManager.put<Sprite>(sprite, enemy);
        _componentManager.put<Animation>(animation, enemy);
        _componentManager.put<Collision>(collision, enemy);
    }

    void GameScene::moveFlyEnemy(Sprite &sprite, Movement &movement)
    {
        if (sprite.getY() > 900)
            movement.setDirection(-3, (rand() % 10) - 10);
        if (sprite.getY() < 50)
            movement.setDirection(-3, (rand() % 10) + 1);
        sprite.setPosition(sprite.getX() + movement.getXDirection(), sprite.getY() + movement.getYDirection());
        
    }

    bool GameScene::destroyFlyEnemy(Sprite &sprite, Animation &animation, entity_t enemy_id)
    {
        (void)enemy_id;
        if ((int)(sprite.getX() + animation.getRectWidth()) < 0) {
            _componentManager.killEntity(enemy_id);
            _entityManager.killEntity(enemy_id);
            return true;
        }
        return false;
    }

    void GameScene::handleFlyEnemy(const int64_t &time)
    {
        std::vector<std::shared_ptr<Entity>> flyEnemies = _entityManager.getEntitiesFromFamily("flyenemy");
        std::shared_ptr<ComponentMap<Movement>> movementMap = _componentManager.getComponents<Movement>();
        std::shared_ptr<ComponentMap<Sprite>> spriteMap = _componentManager.getComponents<Sprite>();
        std::shared_ptr<ComponentMap<Animation>> animationMap = _componentManager.getComponents<Animation>();

        for (auto &flyEnemy : flyEnemies) {
            if (destroyFlyEnemy(spriteMap->get(flyEnemy->getId()), animationMap->get(flyEnemy->getId()), flyEnemy->getId()))
                return handleFlyEnemy(time);
            if (movementMap->contains(flyEnemy->getId()) && spriteMap->contains(flyEnemy->getId())) {
                moveFlyEnemy(spriteMap->get(flyEnemy->getId()), movementMap->get(flyEnemy->getId()));
            }
        }
        if (flyEnemies.size() < 5 && time % 20 == 0)
            spawnFlyEnemy();
    }
}