/*
** EPITECH PROJECT, 2023
** ChildBossEnemy.cpp
** File description:
** ChildBossEnemy's methode
*/

#include "ChildBossEnemy.hpp"

#include "Collision.hpp"
#include "Text.hpp"

#include "GameValues.hpp"
#include "EnemyValues.hpp"

namespace rtype
{
    ChildBossEnemy::ChildBossEnemy(ComponentManager &componentManager, EntityManager &entityManager)
    {
        this->_hp = ENEMY_LIFE.at("childBossEnemy");

        size_t x = 1920 + rand() % 100;
        size_t y = 450 + rand() % 100;

        while (isAlreadyAnEnemyHere(x, y, componentManager, entityManager, "childBossEnemy"))
        {
            x = 1920 + rand() % 500;
            y = rand() % (900 - ENEMY_REACH);
        }

        this->_id = entityManager.spawnEntity("childBossEnemy")->getId();
        Sprite sprite("assets/childBoss.gif", x, y, 6);
        Animation animation(26, 22, 5, 7, 1, 1, 5, 9, 500);
        Movement movement(-3, 0);
        Collision collision({"player"});

        componentManager.put<Sprite>(sprite, this->_id);
        componentManager.put<Animation>(animation, this->_id);
        componentManager.put<Movement>(movement, this->_id);
        componentManager.put<Collision>(collision, this->_id);
    }

    ChildBossEnemy::~ChildBossEnemy()
    {
    }

    void ChildBossEnemy::move(Sprite &sprite, Movement &movement)
    {
        if (sprite.getX() <= 900)
            movement.setDirection(0, 0);
        sprite.setPosition(sprite.getX() + movement.getXDirection(), sprite.getY() + movement.getYDirection());
    }

    bool ChildBossEnemy::destroy(Sprite &sprite, Animation &animation, ComponentManager &componentManager, EntityManager &entityManager)
    {
        if ((int)(sprite.getX() + animation.getRectWidth()) < 0) {
            componentManager.killEntity(this->_id);
            entityManager.killEntity(this->_id);
            return true;
        }
        return false;
    }

    bool ChildBossEnemy::handle(const int64_t &time, ComponentManager &componentManager, EntityManager &entityManager)
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