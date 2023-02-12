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
        Animation animation(21, 24, 5, 6, 8, 1, 12, 0, 500);
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
            // TEMPORARY UNTIL ENEMY DEATH ARE FIX
            sprite.setPosition(2000, rand() % 900);
            //_componentManager.killEntity(enemy_id);
            //_entityManager.killEntity(enemy_id);
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
}