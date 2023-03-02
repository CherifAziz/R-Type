/*
** EPITECH PROJECT, 2023
** BossEnemy.cpp
** File description:
** BossEnemy's methode
*/

#include "BossEnemy.hpp"

#include "Collision.hpp"
#include "Text.hpp"
#include "GameValues.hpp"

namespace rtype
{
    BossEnemy::BossEnemy(ComponentManager &componentManager, EntityManager &entityManager)
    {
        this->_hp = 100;

        size_t x = 1920 + rand() % 100;
        size_t y = rand() % (900 - ENEMY_REACH);

        entity_t enemy = entityManager.spawnEntity("fly")->getId();
        Sprite sprite("assets/BossEnemy.gif", x, y, 3);
        Animation animation(61, 46, 4, 3, 6, 1, 6, 0, 2000);
        Movement movement(-2, 0);
        Collision collision({"player"});

        componentManager.put<Sprite>(sprite, enemy);
        componentManager.put<Animation>(animation, enemy);
        componentManager.put<Movement>(movement, enemy);
        componentManager.put<Collision>(collision, enemy);
    }

    BossEnemy::~BossEnemy()
    {
    }

    void BossEnemy::move(Sprite &sprite, Movement &movement)
    {
        sprite.setPosition(sprite.getX() + movement.getXDirection(), sprite.getY() + movement.getYDirection());
    }

    bool BossEnemy::destroy(Sprite &sprite, Animation &animation, entity_t enemy_id, ComponentManager &componentManager, EntityManager &entityManager)
    {
        (void)enemy_id;
        if ((int)(sprite.getX() + animation.getRectWidth()) < 0)
        {
            componentManager.killEntity(enemy_id);
            entityManager.killEntity(enemy_id);
            return true;
        }
        return false;
    }

    void BossEnemy::handle(const int64_t &time, ComponentManager &componentManager, EntityManager &entityManager)
    {
        std::vector<std::shared_ptr<Entity>> flyEnemies = entityManager.getEntitiesFromFamily("fly");
        std::shared_ptr<ComponentMap<Movement>> movementMap = componentManager.getComponents<Movement>();
        std::shared_ptr<ComponentMap<Sprite>> spriteMap = componentManager.getComponents<Sprite>();
        std::shared_ptr<ComponentMap<Animation>> animationMap = componentManager.getComponents<Animation>();

        for (auto &BossEnemy : flyEnemies)
        {
            if (destroy(spriteMap->get(BossEnemy->getId()), animationMap->get(BossEnemy->getId()), BossEnemy->getId(), componentManager, entityManager))
                return handle(time, componentManager, entityManager);
            if (movementMap->contains(BossEnemy->getId()) && spriteMap->contains(BossEnemy->getId()))
                move(spriteMap->get(BossEnemy->getId()), movementMap->get(BossEnemy->getId()));
        }
    }
}