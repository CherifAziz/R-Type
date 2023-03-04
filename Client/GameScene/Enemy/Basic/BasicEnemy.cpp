/*
** EPITECH PROJECT, 2023
** BasicEnemy
** File description:
** BasicEnemy
*/

#include "BasicEnemy.hpp"
#include "GameScene.hpp"
#include "GameValues.hpp"

#include "Collision.hpp"

namespace rtype 
{
    BasicEnemy::BasicEnemy(ComponentManager &componentManager, EntityManager &entityManager)
    {
        this->_hp = 1;

        size_t x = 1920 + rand() % 100;
        size_t y = rand() % (900 - ENEMY_REACH);

        while (isAlreadyAnEnemyHere(x, y, componentManager, entityManager, "basicEnemy")) {
            x = 1920 + rand() % 500;
            y = rand() % (900 - ENEMY_REACH);
        }
        this->_id = entityManager.spawnEntity("basicEnemy")->getId();
        Sprite sprite("assets/basicEnemy.gif", x, y, 4);
        Animation animation(20, 30, 5, 7, 8, 1, 12, 0, 500);
        Movement movement(-5, 3);
        Collision collision({"player"});

        componentManager.put<Sprite>(sprite, this->_id);
        componentManager.put<Animation>(animation, this->_id);
        componentManager.put<Movement>(movement, this->_id);
        componentManager.put<Collision>(collision, this->_id);
    }

    BasicEnemy::~BasicEnemy()
    {
    }

    void BasicEnemy::move(Sprite &sprite, Movement &movement)
    {
        if (sprite.getY() > 900)
            movement.setDirection(-7, -9);
        if (sprite.getY() < 50)
            movement.setDirection(2, 9);
        sprite.setPosition(sprite.getX() + movement.getXDirection(), sprite.getY() + movement.getYDirection());
    }

    bool BasicEnemy::destroy(Sprite &sprite, Animation &animation, ComponentManager &componentManager, EntityManager &entityManager)
    {
        if ((int)(sprite.getX() + animation.getRectWidth()) < 0) {
            componentManager.killEntity(this->_id);
            entityManager.killEntity(this->_id);
            return true;
        }
        return false;
    }

    bool BasicEnemy::handle(const int64_t &time, ComponentManager &componentManager, EntityManager &entityManager)
    {
        Movement &movement = componentManager.get<Movement>(this->_id);
        Sprite &sprite = componentManager.get<Sprite>(this->_id);
        Animation &animation = componentManager.get<Animation>(this->_id);

        if (destroy(sprite, animation, componentManager, entityManager))
            return true;
        move(sprite, movement);
        return false;
    }
}
