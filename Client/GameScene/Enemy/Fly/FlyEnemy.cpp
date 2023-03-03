/*
** EPITECH PROJECT, 2023
** FlyEnemy.cpp
** File description:
** flyenemy's methode
*/

#include "FlyEnemy.hpp"

#include "Collision.hpp"
#include "Text.hpp"
#include "GameValues.hpp"

namespace rtype
{
    bool isAlreadyAnFlyEnemyHere(size_t x, size_t y, ComponentManager &componentManager, EntityManager &entityManager)
    {
        std::vector<std::shared_ptr<Entity>> flyEnemies = entityManager.getEntitiesFromFamily("fly");

        for (auto &flyEnemy : flyEnemies) {
            Sprite &sprite = componentManager.get<Sprite>(flyEnemy->getId());

            if ((int)x > sprite.getX() - ENEMY_REACH && (int)x < sprite.getX() + ENEMY_REACH)
                return true;
            else if ((int)y > sprite.getY() - ENEMY_REACH && (int)y < sprite.getY() + ENEMY_REACH)
                return true;
        }
        return false;
    }

    FlyEnemy::FlyEnemy(ComponentManager &componentManager, EntityManager &entityManager)
    {
        this->_hp = 10;

        size_t x = 1920 + rand() % 100;
        size_t y = rand() % (900 - ENEMY_REACH);

        while (isAlreadyAnFlyEnemyHere(x, y, componentManager, entityManager))
        {
            x = 1920 + rand() % 500;
            y = rand() % (900 - ENEMY_REACH);
        }
        this->_id = entityManager.spawnEntity("fly")->getId();
        Sprite sprite("assets/flyenemy.gif", x, y, 3);
        Animation animation(61, 46, 4, 3, 6, 1, 6, 0, 2000);
        Movement movement(-2, 2);
        Collision collision({"player"});

        componentManager.put<Sprite>(sprite, this->_id);
        componentManager.put<Animation>(animation, this->_id);
        componentManager.put<Movement>(movement, this->_id);
        componentManager.put<Collision>(collision, this->_id);
    }

    FlyEnemy::~FlyEnemy()
    {
    }

    void FlyEnemy::move(Sprite &sprite, Movement &movement)
     {
        if (sprite.getY() > 900)
            movement.setDirection((rand() % 5) -6, (rand() % 10) - 10);
        if (sprite.getY() < 50)
            movement.setDirection((rand() % 5) - 6, (rand() % 10) + 1);
        sprite.setPosition(sprite.getX() + movement.getXDirection(), sprite.getY() + movement.getYDirection());
    }

    bool FlyEnemy::destroy(Sprite &sprite, Animation &animation, ComponentManager &componentManager, EntityManager &entityManager)
    {
        if ((int)(sprite.getX() + animation.getRectWidth()) < 0) {
            componentManager.killEntity(this->_id);
            entityManager.killEntity(this->_id);
            return true;
        }
        return false;
    }

    bool FlyEnemy::handle(const int64_t &time, ComponentManager &componentManager, EntityManager &entityManager)
    {
        std::vector<std::shared_ptr<Entity>> flyEnemies = entityManager.getEntitiesFromFamily("fly");
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