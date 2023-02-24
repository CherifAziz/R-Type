/*
** EPITECH PROJECT, 2023
** MediumEnemy
** File description:
** MediumEnemy
*/

#include "GameScene.hpp"
#include "GameValues.hpp"

#include "Collision.hpp"

namespace rtype
{
    bool GameScene::isAlreadyMediumEnemyHere(size_t x, size_t y)
    {
        std::vector<std::shared_ptr<Entity>> mediumEnemies = _entityManager.getEntitiesFromFamily("mediumEnemy");

        for (auto &mediumEnemy : mediumEnemies)
        {
            Sprite &sprite = _componentManager.get<Sprite>(mediumEnemy->getId());

            if ((int)x > sprite.getX() - ENEMY_REACH && (int)x < sprite.getX() + ENEMY_REACH)
                return true;
            else if ((int)y > sprite.getY() - ENEMY_REACH && (int)y < sprite.getY() + ENEMY_REACH)
                return true;
        }
        return false;
    }

    void GameScene::spawnMediumEnemy()
    {
        size_t x = 1920 + rand() % 100;
        size_t y = rand() % (900 - ENEMY_REACH);

        while (isAlreadyMediumEnemyHere(x, y))
        {
            x = 1920 + rand() % 500;
            y = rand() % (900 - ENEMY_REACH);
        }
        entity_t enemy = _entityManager.spawnEntity("mediumEnemy")->getId();
        Sprite sprite("assets/mediumEnemy.gif", x, y, 4);
        Animation animation(33, 32, 1, 1, 3, 1, 1, 0, 500);
        Movement movement(-3, 0);
        Collision collision({"player"});

        _componentManager.put<Sprite>(sprite, enemy);
        _componentManager.put<Animation>(animation, enemy);
        _componentManager.put<Movement>(movement, enemy);
        _componentManager.put<Collision>(collision, enemy);
    }

    void GameScene::moveMediumEnemy(Sprite &sprite, Movement &movement)
    {
        sprite.setPosition(sprite.getX() + movement.getXDirection(), sprite.getY() + movement.getYDirection());
    }

    bool GameScene::destroyMediumEnemy(Sprite &sprite, Animation &animation, entity_t enemy_id)
    {
        (void)enemy_id;
        if ((int)(sprite.getX() + animation.getRectWidth()) < 0) {
            _componentManager.killEntity(enemy_id);
            _entityManager.killEntity(enemy_id);
            return true;
        }
        return false;
    }

    void GameScene::handleMediumEnemy(const int64_t &time)
    {
        std::vector<std::shared_ptr<Entity>> mediumEnemies = _entityManager.getEntitiesFromFamily("mediumEnemy");
        std::shared_ptr<ComponentMap<Movement>> movementMap = _componentManager.getComponents<Movement>();
        std::shared_ptr<ComponentMap<Sprite>> spriteMap = _componentManager.getComponents<Sprite>();
        std::shared_ptr<ComponentMap<Animation>> animationMap = _componentManager.getComponents<Animation>();

        for (auto &mediumEnemy : mediumEnemies)
        {
            if (destroyMediumEnemy(spriteMap->get(mediumEnemy->getId()), animationMap->get(mediumEnemy->getId()), mediumEnemy->getId()))
                return handleMediumEnemy(time);
            if (movementMap->contains(mediumEnemy->getId()) && spriteMap->contains(mediumEnemy->getId()))
                moveMediumEnemy(spriteMap->get(mediumEnemy->getId()), movementMap->get(mediumEnemy->getId()));
        }
        if (mediumEnemies.size() < 3 && time % 20 == 0)
            spawnMediumEnemy();
    }
}