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
    bool isAlreadyAnBossEnemyHere(size_t x, size_t y)
    {
        std::vector<std::shared_ptr<Entity>> flyEnemies = _entityManager.getEntitiesFromFamily("fly");

        for (auto &BossEnemy : flyEnemies) {
            Sprite &sprite = _componentManager.get<Sprite>(BossEnemy->getId());

            if ((int)x > sprite.getX() - ENEMY_REACH && (int)x < sprite.getX() + ENEMY_REACH)
                return true;
            else if ((int)y > sprite.getY() - ENEMY_REACH && (int)y < sprite.getY() + ENEMY_REACH)
                return true;
        }
        return false;
    }

    BossEnemy::BossEnemy(ComponentManager &componentManager, EntityManager &entityManager)
    {
        this->_hp = 10;


        size_t x = 1920 + rand() % 100;
        size_t y = rand() % (900 - ENEMY_REACH);

        while (isAlreadyAnBossEnemyHere(x, y))
        {
            x = 1920 + rand() % 500;
            y = rand() % (900 - ENEMY_REACH);
        }
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

    bool BossEnemy::destroy(ComponentManager &componentManager, EntityManager &entityManager)
    {
        (void)enemy_id;
        if ((int)(sprite.getX() + animation.getRectWidth()) < 0)
        {
            _componentManager.killEntity(enemy_id);
            _entityManager.killEntity(enemy_id);
            return true;
        }
        return false;
    }

    void BossEnemy::handle(const int64_t &time)
    {
        std::vector<std::shared_ptr<Entity>> flyEnemies = _entityManager.getEntitiesFromFamily("fly");
        std::shared_ptr<ComponentMap<Movement>> movementMap = _componentManager.getComponents<Movement>();
        std::shared_ptr<ComponentMap<Sprite>> spriteMap = _componentManager.getComponents<Sprite>();
        std::shared_ptr<ComponentMap<Animation>> animationMap = _componentManager.getComponents<Animation>();

        for (auto &BossEnemy : flyEnemies)
        {
            if (destroyBossEnemy(spriteMap->get(BossEnemy->getId()), animationMap->get(BossEnemy->getId()), BossEnemy->getId()))
                return handleBossEnemy(time);
            if (movementMap->contains(BossEnemy->getId()) && spriteMap->contains(BossEnemy->getId()))
                moveBossEnemy(spriteMap->get(BossEnemy->getId()), movementMap->get(BossEnemy->getId()));
        }
        if (flyEnemies.size() < 5 && time % 20 == 0)
        {
            spawnBossEnemy();
        }
    }
}