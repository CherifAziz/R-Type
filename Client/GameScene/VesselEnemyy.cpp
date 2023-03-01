/*
** EPITECH PROJECT, 2023
** Vessel
** File description:
** Vessel
*/

#include "GameScene.hpp"
#include "GameValues.hpp"

#include "Collision.hpp"

namespace rtype {
    bool GameScene::isAlreadyVesselHere(size_t x, size_t y)
    {
        std::vector<std::shared_ptr<Entity>> vesselEnemies = _entityManager.getEntitiesFromFamily("vessel");

        for (auto &vesselEnemy : vesselEnemies) {
            Sprite &sprite = _componentManager.get<Sprite>(vesselEnemy->getId());

            if ((int)x > sprite.getX() - ENEMY_REACH && (int)x < sprite.getX() + ENEMY_REACH)
                return true;
            else if ((int)y > sprite.getY() - ENEMY_REACH && (int)y < sprite.getY() + ENEMY_REACH)
                return true;
        }
        return false;
    }

    void GameScene::spawnVessel()
    {
        size_t x = 1920 + rand() % 100;
        size_t y = rand() % (900 - ENEMY_REACH);

        while (isAlreadyVesselHere(x, y)) {
            x = 1920 + rand() % 500;
            y = rand() % (900 - ENEMY_REACH);
        }
        entity_t enemy = _entityManager.spawnEntity("vessel")->getId();
        Sprite sprite("assets/r-typesheet26.gif", x, y, 3);
        Animation animation(63, 49, 1, 1, 3, 1, 2, 1, 500);
        Movement movement(-5, 0);
        Collision collision({"player"});

        _componentManager.put<Sprite>(sprite, enemy);
        _componentManager.put<Animation>(animation, enemy);
        _componentManager.put<Movement>(movement, enemy);
        _componentManager.put<Collision>(collision, enemy);
    }

    void GameScene::moveVessel(Sprite &sprite, Movement &movement)
    {
        sprite.setPosition(sprite.getX() + movement.getXDirection(), sprite.getY() + movement.getYDirection());
    }

    bool GameScene::destroyVessel(Sprite &sprite, Animation &animation, entity_t enemy_id)
    {
        (void)enemy_id;
        if ((int)(sprite.getX() + animation.getRectWidth()) < 0) {
            _componentManager.killEntity(enemy_id);
            _entityManager.killEntity(enemy_id);
            return true;
        }
        return false;
    }

    void GameScene::handleVessel(const int64_t &time)
    {
        std::vector<std::shared_ptr<Entity>> vesselEnemies = _entityManager.getEntitiesFromFamily("vessel");
        std::shared_ptr<ComponentMap<Movement>> movementMap = _componentManager.getComponents<Movement>();
        std::shared_ptr<ComponentMap<Sprite>> spriteMap = _componentManager.getComponents<Sprite>();
        std::shared_ptr<ComponentMap<Animation>> animationMap = _componentManager.getComponents<Animation>();
        int familyIndex = 0;

        for (auto &vesselEnemy : vesselEnemies) {
            if (destroyVessel(spriteMap->get(vesselEnemy->getId()), animationMap->get(vesselEnemy->getId()), vesselEnemy->getId()))
                return handleVessel(time);
            if (movementMap->contains(vesselEnemy->getId()) && spriteMap->contains(vesselEnemy->getId()))
                moveVessel(spriteMap->get(vesselEnemy->getId()), movementMap->get(vesselEnemy->getId()));
        }
        familyIndex = GetFamilyIndex("vessel");
        if (vesselEnemies.size() < 5 && time % 20 == 0 && familyIndex != -1)
            if (waves[0][familyIndex].second != 0)
                spawnVessel();
    }
}