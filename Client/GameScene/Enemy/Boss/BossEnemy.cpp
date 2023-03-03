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
    bool isAlreadyAnBossHere(size_t x, size_t y, ComponentManager &componentManager, EntityManager &entityManager)
    {
        std::vector<std::shared_ptr<Entity>> bossEnemies = entityManager.getEntitiesFromFamily("boss");

        for (auto &bossEnemy : bossEnemies) {
            Sprite &sprite = componentManager.get<Sprite>(bossEnemy->getId());

            if ((int)x > sprite.getX() - ENEMY_REACH && (int)x < sprite.getX() + ENEMY_REACH)
                return true;
            else if ((int)y > sprite.getY() - ENEMY_REACH && (int)y < sprite.getY() + ENEMY_REACH)
                return true;
        }
        return false;
    }

    BossEnemy::BossEnemy(ComponentManager &componentManager, EntityManager &entityManager)
    {
        this->_hp = 100;

        size_t x = 800;
        size_t y = 450;

        while (isAlreadyAnBossHere(x, y, componentManager, entityManager))
        {
            x = 1920 + rand() % 500;
            y = rand() % (900 - ENEMY_REACH);
        }

        this->_id = entityManager.spawnEntity("boss")->getId();
        Sprite sprite("assets/boss1.gif", x, y, 4);
        Animation animation(255, 142, 0, 0, 2, 4, 5, 3, 2000);
        Movement movement(1, 0);
        Collision collision({"player"});

        componentManager.put<Sprite>(sprite, this->_id);
        componentManager.put<Animation>(animation, this->_id);
        componentManager.put<Movement>(movement, this->_id);
        componentManager.put<Collision>(collision, this->_id);
    }

    BossEnemy::~BossEnemy()
    {
    }

    void BossEnemy::move(Sprite &sprite, Movement &movement)
    {
        sprite.setPosition(sprite.getX() + movement.getXDirection(), sprite.getY() + movement.getYDirection());
    }

    bool BossEnemy::destroy(Sprite &sprite, Animation &animation, ComponentManager &componentManager, EntityManager &entityManager)
    {
        if ((int)(sprite.getX() + animation.getRectWidth()) < 0) {
            componentManager.killEntity(this->_id);
            entityManager.killEntity(this->_id);
            return true;
        }
        return false;
    }

    bool BossEnemy::handle(const int64_t &time, ComponentManager &componentManager, EntityManager &entityManager)
    {
        std::vector<std::shared_ptr<Entity>> flyEnemies = entityManager.getEntitiesFromFamily("boss");
        std::shared_ptr<ComponentMap<Movement>> movementMap = componentManager.getComponents<Movement>();
        std::shared_ptr<ComponentMap<Sprite>> spriteMap = componentManager.getComponents<Sprite>();
        std::shared_ptr<ComponentMap<Animation>> animationMap = componentManager.getComponents<Animation>();

        if (destroy(spriteMap->get(this->_id), animationMap->get(this->_id), componentManager, entityManager))
            return true;
        if (movementMap->contains(this->_id) && spriteMap->contains(this->_id))
            move(spriteMap->get(this->_id), movementMap->get(this->_id));
        return false;
    }
}