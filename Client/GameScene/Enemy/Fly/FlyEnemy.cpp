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
        entity_t enemy = entityManager.spawnEntity("fly")->getId();
        Sprite sprite("assets/flyenemy.gif", x, y, 3);
        Animation animation(61, 46, 4, 3, 6, 1, 6, 0, 2000);
        Movement movement(-2, 0);
        Collision collision({"player"});

        componentManager.put<Sprite>(sprite, enemy);
        componentManager.put<Animation>(animation, enemy);
        componentManager.put<Movement>(movement, enemy);
        componentManager.put<Collision>(collision, enemy);
    }

    FlyEnemy::~FlyEnemy()
    {
    }

    void FlyEnemy::move(Sprite &sprite, Movement &movement)
    {
        sprite.setPosition(sprite.getX() + movement.getXDirection(), sprite.getY() + movement.getYDirection());
    }

    bool FlyEnemy::destroy(ComponentManager &componentManager, EntityManager &entityManager)
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

    void FlyEnemy::handle(const int64_t &time, ComponentManager &componentManager, EntityManager &entityManager)
    {
        std::vector<std::shared_ptr<Entity>> flyEnemies = entityManager.getEntitiesFromFamily("fly");
        std::shared_ptr<ComponentMap<Movement>> movementMap = componentManager.getComponents<Movement>();
        std::shared_ptr<ComponentMap<Sprite>> spriteMap = componentManager.getComponents<Sprite>();
        std::shared_ptr<ComponentMap<Animation>> animationMap = componentManager.getComponents<Animation>();

        for (auto &flyEnemy : flyEnemies)
        {
            if (destroy(spriteMap->get(flyEnemy->getId()), animationMap->get(flyEnemy->getId()), flyEnemy->getId()))
                return handle(time);
            if (movementMap->contains(flyEnemy->getId()) && spriteMap->contains(flyEnemy->getId()))
                move(spriteMap->get(flyEnemy->getId()), movementMap->get(flyEnemy->getId()));
        }
    }
}