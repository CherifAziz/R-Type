/*
** EPITECH PROJECT, 2023
** VesselEnemy
** File description:
** VesselEnemy
*/

#include "VesselEnemy.hpp"
#include "GameValues.hpp"

#include "GameScene.hpp"

#include "Collision.hpp"

namespace rtype {
    VesselEnemy::VesselEnemy(ComponentManager &componentManager, EntityManager &entityManager)
    {
        this->_hp = 30;
        size_t x = 1920 + rand() % 100;
        size_t y = rand() % (900 - ENEMY_REACH);

        while (isAlreadyAnEnemyHere(x, y, componentManager, entityManager, "vesselEnemy")) {
            x = 1920 + rand() % 500;
            y = rand() % (900 - ENEMY_REACH);
        }
        entity_t enemy = entityManager.spawnEntity("vesselEnemy")->getId();
        Sprite sprite("assets/r-typesheet26.gif", x, y, 3);
        Animation animation(63, 49, 1, 1, 3, 1, 2, 1, 500);
        Movement movement(-5, 0);
        Collision collision({"player"});

        componentManager.put<Sprite>(sprite, enemy);
        componentManager.put<Animation>(animation, enemy);
        componentManager.put<Movement>(movement, enemy);
        componentManager.put<Collision>(collision, enemy);
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
        std::vector<std::shared_ptr<Entity>> vesselEnemies = entityManager.getEntitiesFromFamily("vesselEnemy");
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