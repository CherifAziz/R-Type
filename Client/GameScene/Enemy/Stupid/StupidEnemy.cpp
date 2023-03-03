/*
** EPITECH PROJECT, 2023
** StupidEnemy
** File description:
** StupidEnemy
*/

#include "StupidEnemy.hpp"
#include "GameValues.hpp"

#include "GameScene.hpp"

#include "Collision.hpp"

namespace rtype {
    StupidEnemy::StupidEnemy(ComponentManager &componentManager, EntityManager &entityManager)
    {
        this->_hp = 15;
        size_t x = 1920 + rand() % 100;
        size_t y = rand() % (900 - ENEMY_REACH);

        while (isAlreadyAnEnemyHere(x, y, componentManager, entityManager, "stupidEnemy"))
        {
            x = 1920 + rand() % 500;
            y = rand() % (900 - ENEMY_REACH);
        }
        entity_t enemy = entityManager.spawnEntity("stupidEnemy")->getId();
        Sprite sprite("assets/mediumEnemy.gif", x, y, 4);
        Animation animation(33, 32, 1, 1, 3, 1, 1, 0, 500);
        Movement movement(-3, 0);
        Collision collision({"player"});

        componentManager.put<Sprite>(sprite, enemy);
        componentManager.put<Animation>(animation, enemy);
        componentManager.put<Movement>(movement, enemy);
        componentManager.put<Collision>(collision, enemy);
    }

    StupidEnemy::~StupidEnemy()
    {

    }

    void StupidEnemy::move(Sprite &sprite, Movement &movement)
    {
        sprite.setPosition(sprite.getX() + movement.getXDirection(), sprite.getY() + movement.getYDirection());
    }

    bool StupidEnemy::destroy(Sprite &sprite, Animation &animation, ComponentManager &componentManager, EntityManager &entityManager)
    {
        if ((int)(sprite.getX() + animation.getRectWidth()) < 0) {
            componentManager.killEntity(_id);
            entityManager.killEntity(_id);
            return true;
        }
        return false;
    }

    bool StupidEnemy::handle(const int64_t &time, ComponentManager &componentManager, EntityManager &entityManager)
    {
        std::vector<std::shared_ptr<Entity>> mediumEnemies = entityManager.getEntitiesFromFamily("stupidEnemy");
        std::shared_ptr<ComponentMap<Movement>> movementMap = componentManager.getComponents<Movement>();
        std::shared_ptr<ComponentMap<Sprite>> spriteMap = componentManager.getComponents<Sprite>();
        std::shared_ptr<ComponentMap<Animation>> animationMap = componentManager.getComponents<Animation>();

        if (destroy(spriteMap->get(_id), animationMap->get(_id), componentManager, entityManager))
            return true;
        if (movementMap->contains(this->_id) && spriteMap->contains(this->_id))
            move(spriteMap->get(this->_id), movementMap->get(this->_id));
        return false;
    }
}