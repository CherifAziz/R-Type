/*
** EPITECH PROJECT, 2023
** BossEnemy.cpp
** File description:
** BossEnemy's methode
*/

#include "config.hpp"
#include "BossEnemy.hpp"

#include "Collision.hpp"
#include "Text.hpp"

#include "GameValues.hpp"
#include "EnemyValues.hpp"

namespace rtype
{
    BossEnemy::BossEnemy(ComponentManager &componentManager, EntityManager &entityManager, const size_t &windowWidth, const size_t &windowHeight)
    {
        this->_hp = ENEMY_LIFE.at("bossEnemy");

        size_t x = windowWidth + rand() % 100;
        size_t y = (windowHeight / 2) + rand() % 100;

        while (isAlreadyAnEnemyHere(x, y, componentManager, entityManager, "bossEnemy"))
        {
            x = windowWidth + rand() % 500;
            y = rand() % (windowHeight - ENEMY_REACH);
        }

        this->_id = entityManager.spawnEntity("bossEnemy")->getId();
        Sprite sprite(std::string(ASSETS_DIR)+"boss1.gif", x, y, 4);
        Animation animation(255, 142, 0, 0, 2, 4, 5, 3, 2000);
        Movement movement(-3, 0);
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
        if (sprite.getX() <= 900)
            movement.setDirection(0, 0);
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

    bool BossEnemy::handle(const int64_t &time, ComponentManager &componentManager, EntityManager &entityManager, const size_t &windowWidth, const size_t &windowHeight)
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