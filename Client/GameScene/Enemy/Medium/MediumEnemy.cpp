/*
** EPITECH PROJECT, 2023
** MediumEnemy
** File description:
** MediumEnemy
*/

#include "config.hpp"
#include "MediumEnemy.hpp"

#include "GameValues.hpp"
#include "EnemyValues.hpp"

#include "GameScene.hpp"

#include "Collision.hpp"

namespace rtype {
    MediumEnemy::MediumEnemy(ComponentManager &componentManager, EntityManager &entityManager, const size_t &windowWidth, const size_t &windowHeight)
    {
        this->_hp = ENEMY_LIFE.at("mediumEnemy");

        size_t x = windowWidth + rand() % 100;
        size_t y = rand() % (windowHeight - ENEMY_REACH - 100);

        while (isAlreadyAnEnemyHere(x, y, componentManager, entityManager, "mediumEnemy")) {
            x = windowWidth + rand() % 500;
            y = rand() % (windowHeight - ENEMY_REACH - 100);
        }
        this->_id = entityManager.spawnEntity("mediumEnemy")->getId();
        Sprite sprite(std::string(ASSETS_DIR)+"mediumEnemy.gif", x, y, 4);
        Animation animation(33, 32, 1, 1, 3, 1, 1, 0, 500);
        Movement movement(-3, 0);
        Collision collision({"player"});

        componentManager.put<Sprite>(sprite, _id);
        componentManager.put<Animation>(animation, _id);
        componentManager.put<Movement>(movement, _id);
        componentManager.put<Collision>(collision, _id);
    }

    MediumEnemy::~MediumEnemy()
    {

    }

    void MediumEnemy::move(Sprite &sprite, Movement &movement)
    {
        sprite.setPosition(sprite.getX() + movement.getXDirection(), sprite.getY() + movement.getYDirection());
    }

    bool MediumEnemy::destroy(Sprite &sprite, Animation &animation, ComponentManager &componentManager, EntityManager &entityManager)
    {
        if ((int)(sprite.getX() + animation.getRectWidth()) < 0) {
            componentManager.killEntity(_id);
            entityManager.killEntity(_id);
            return true;
        }
        return false;
    }

    bool MediumEnemy::handle(const int64_t &time, ComponentManager &componentManager, EntityManager &entityManager, const size_t &windowWidth, const size_t &windowHeight)
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