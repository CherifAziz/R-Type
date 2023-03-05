/*
** EPITECH PROJECT, 2023
** FlyEnemy.cpp
** File description:
** flyenemy's methode
*/

#include "config.hpp"
#include "FlyEnemy.hpp"

#include "Collision.hpp"
#include "Text.hpp"

#include "GameValues.hpp"
#include "EnemyValues.hpp"

namespace rtype
{
    FlyEnemy::FlyEnemy(ComponentManager &componentManager, EntityManager &entityManager, const size_t &windowWidth, const size_t &windowHeight)
    {
        this->_hp = ENEMY_LIFE.at("flyEnemy");

        size_t x = windowWidth + rand() % 100;
        size_t y = rand() % (windowHeight - ENEMY_REACH - 100);

        while (isAlreadyAnEnemyHere(x, y, componentManager, entityManager, "flyEnemy"))
        {
            x = windowWidth + rand() % 500;
            y = rand() % (windowHeight - ENEMY_REACH - 100);
        }
        this->_id = entityManager.spawnEntity("flyEnemy")->getId();
        Sprite sprite(std::string(ASSETS_DIR)+"flyenemy.gif", x, y, 3);
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

    void FlyEnemy::move(Sprite &sprite, Movement &movement, Animation &animation, const size_t &windowWidth, const size_t &windowHeight)
     {
        if (sprite.getY() > windowHeight - animation.getRectHeight() * sprite.getScale())
            movement.setDirection((rand() % 5) -6, (rand() % 10) - 10);
        if (sprite.getY() < 0)
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

    bool FlyEnemy::handle(const int64_t &time, ComponentManager &componentManager, EntityManager &entityManager, const size_t &windowWidth, const size_t &windowHeight)
    {
        Movement &movement = componentManager.get<Movement>(this->_id);
        Sprite &sprite = componentManager.get<Sprite>(this->_id);
        Animation &animation = componentManager.get<Animation>(this->_id);

        if (destroy(sprite, animation, componentManager, entityManager))
            return true;
        move(sprite, movement, animation, windowWidth, windowHeight);
        return false;
    }
}