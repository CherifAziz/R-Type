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
        entity_t enemy = entityManager.spawnEntity("basicEnemy")->getId();
        Sprite sprite("assets/basicEnemy.gif", x, y, 4);
        Animation animation(20, 30, 5, 7, 8, 1, 12, 0, 500);
        Movement movement(-5, 0);
        Collision collision({"player"});

        componentManager.put<Sprite>(sprite, enemy);
        componentManager.put<Animation>(animation, enemy);
        componentManager.put<Movement>(movement, enemy);
        componentManager.put<Collision>(collision, enemy);
    }


    void BasicEnemy::move(Sprite &sprite, Movement &movement)
    {
        if (sprite.getY() > 900)
            movement.setDirection(-5, -4);
        if (sprite.getY() < 50)
            movement.setDirection(3, 4);
        sprite.setPosition(sprite.getX() + movement.getXDirection(), sprite.getY() + movement.getYDirection());
    }

    bool BasicEnemy::destroy(Sprite &sprite, Animation &animation, entity_t enemy_id, ComponentManager &componentManager, EntityManager &entityManager)
    {
        (void)enemy_id;
        if ((int)(sprite.getX() + animation.getRectWidth()) < 0) {
            componentManager.killEntity(enemy_id);
            entityManager.killEntity(enemy_id);
            return true;
        }
        return false;
    }

    void BasicEnemy::handle(const int64_t &time, ComponentManager &componentManager, EntityManager &entityManager)
    {
        std::vector<std::shared_ptr<Entity>> basicEnemies = entityManager.getEntitiesFromFamily("basicEnemy");
        std::shared_ptr<ComponentMap<Movement>> movementMap = componentManager.getComponents<Movement>();
        std::shared_ptr<ComponentMap<Sprite>> spriteMap = componentManager.getComponents<Sprite>();
        std::shared_ptr<ComponentMap<Animation>> animationMap = componentManager.getComponents<Animation>();

        for (auto &basicEnemy : basicEnemies) {
            if (destroy(spriteMap->get(basicEnemy->getId()), animationMap->get(basicEnemy->getId()), basicEnemy->getId(), componentManager, entityManager))
                return handle(time, componentManager, entityManager);
            if (movementMap->contains(basicEnemy->getId()) && spriteMap->contains(basicEnemy->getId()))
                move(spriteMap->get(basicEnemy->getId()), movementMap->get(basicEnemy->getId()));
        }
    }

    BasicEnemy::~BasicEnemy()
    {
    }
}
