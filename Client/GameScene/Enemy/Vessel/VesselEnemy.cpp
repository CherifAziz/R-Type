/*
** EPITECH PROJECT, 2023
** VesselEnemy
** File description:
** VesselEnemy
*/

#include "VesselEnemy.hpp"

#include "GameValues.hpp"
#include "EnemyValues.hpp"

#include "GameScene.hpp"

#include "Collision.hpp"

namespace rtype {
    VesselEnemy::VesselEnemy(ComponentManager &componentManager, EntityManager &entityManager)
    {
        this->_hp = ENEMY_LIFE.at("vesselEnemy");

        size_t x = 1920 + rand() % 100;
        size_t y = rand() % (900 - ENEMY_REACH);

        while (isAlreadyAnEnemyHere(x, y, componentManager, entityManager, "vesselEnemy")) {
            x = 1920 + rand() % 500;
            y = rand() % (900 - ENEMY_REACH);
        }
        this->_id = entityManager.spawnEntity("vesselEnemy")->getId();
        Sprite sprite("assets/r-typesheet26.gif", x, y, 3);
        Animation animation(63, 49, 1, 1, 3, 1, 2, 1, 500);
        Movement movement(-5, 0);
        Collision collision({"player"});

        componentManager.put<Sprite>(sprite, _id);
        componentManager.put<Animation>(animation, _id);
        componentManager.put<Movement>(movement, _id);
        componentManager.put<Collision>(collision, _id);
    }

    VesselEnemy::~VesselEnemy()
    {

    }

    void VesselEnemy::move(Sprite &sprite, Movement &movement)
    {
        sprite.setPosition(sprite.getX() + movement.getXDirection(), sprite.getY() + movement.getYDirection());
    }

    bool VesselEnemy::destroy(Sprite &sprite, Animation &animation, ComponentManager &componentManager, EntityManager &entityManager)
    {
        if ((int)(sprite.getX() + animation.getRectWidth()) < 0) {
            componentManager.killEntity(_id);
            entityManager.killEntity(_id);
            return true;
        }
        return false;
    }

    bool VesselEnemy::handle(const int64_t &time, ComponentManager &componentManager, EntityManager &entityManager)
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