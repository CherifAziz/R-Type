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
    bool isAlreadyAnEnemyHere(size_t x, size_t y, ComponentManager &componentManager, EntityManager &entityManager)
    {
        std::vector<std::shared_ptr<Entity>> basicEnemies = entityManager.getEntitiesFromFamily("basicEnemy");

        for (auto &basicEnemy : basicEnemies) {
            Sprite &sprite = componentManager.get<Sprite>(basicEnemy->getId());

            if ((int)x > sprite.getX() - ENEMY_REACH && (int)x < sprite.getX() + ENEMY_REACH)
                return true;
            else if ((int)y > sprite.getY() - ENEMY_REACH && (int)y < sprite.getY() + ENEMY_REACH)
                return true;
        }
        return false;
    }

    BasicEnemy::BasicEnemy(ComponentManager &componentManager, EntityManager &entityManager)
    {
        this->_hp = 1;

        size_t x = 1920 + rand() % 100;
        size_t y = rand() % (900 - ENEMY_REACH);

        while (isAlreadyAnEnemyHere(x, y, componentManager, entityManager)) {
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
        std::vector<std::shared_ptr<Entity>> basicEnemies = entityManager.getEntitiesFromFamily("basicEnemy");
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
