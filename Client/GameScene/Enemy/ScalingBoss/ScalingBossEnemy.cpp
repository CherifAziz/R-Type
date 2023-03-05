/*
** EPITECH PROJECT, 2023
** ScalingBossEnemy.cpp
** File description:
** ScalingBossEnemy's methode
*/

#include "ScalingBossEnemy.hpp"

#include "Collision.hpp"
#include "Text.hpp"

#include "GameValues.hpp"
#include "EnemyValues.hpp"

namespace rtype
{
    ScalingBossEnemy::ScalingBossEnemy(ComponentManager &componentManager, EntityManager &entityManager, const size_t &windowWidth, const size_t &windowHeight)
    {
        this->_hp = ENEMY_LIFE.at("scalingBossEnemy");
        this->_lastHp = this->_hp;

        size_t x = windowWidth;
        size_t y = windowHeight / 2;

        while (isAlreadyAnEnemyHere(x, y, componentManager, entityManager, "scalingBossEnemy"))
        {
            x = windowWidth + rand() % 500;
            y = rand() % (windowHeight - ENEMY_REACH - 100);
        }
        this->_id = entityManager.spawnEntity("scalingBossEnemy")->getId();
        Sprite sprite("assets/scalingboss.gif", x, y, 10);
        Animation animation(31, 31, 0, 0, 3, 1, 3, 0, 2000);
        Movement movement(-3, 0);
        Collision collision({"player"});

        componentManager.put<Sprite>(sprite, this->_id);
        componentManager.put<Animation>(animation, this->_id);
        componentManager.put<Movement>(movement, this->_id);
        componentManager.put<Collision>(collision, this->_id);
    }

    ScalingBossEnemy::~ScalingBossEnemy()
    {
    }

    void ScalingBossEnemy::move(Sprite &player_sprite, Sprite &sprite, Movement &movement, Animation &animation, const size_t &windowWidth, const size_t &windowHeight)
    {   

        if (sprite.getX() > windowWidth - 32 * sprite.getScale()){
            sprite.setPosition(sprite.getX() + movement.getXDirection(), sprite.getY() + movement.getYDirection());
        } else {
            static const int defaultSpeed = movement.getXDirection();
            double Speed = defaultSpeed > 0 ? defaultSpeed + (sprite.getScale() * 0.1) : defaultSpeed - (sprite.getScale() * 0.1);
            int x_direction = player_sprite.getX() + (16 * player_sprite.getScale()) < sprite.getX() + (16 * sprite.getScale()) ? 1 : -1;
            int y_direction = player_sprite.getY() + (7 * player_sprite.getScale()) < sprite.getY() + (14 * sprite.getScale()) ? 1 : -1;
            if (this->_lastHp > this->_hp) {
                sprite.setScale(sprite.getScale() + 0.2);
                this->_lastHp = this->_hp;
            }
            sprite.setPosition(sprite.getX() + (movement.getXDirection() * x_direction), sprite.getY() + (movement.getYDirection() * y_direction));
            movement.setDirection(Speed, Speed);
        }
    }

    bool ScalingBossEnemy::destroy(Sprite &sprite, Animation &animation, ComponentManager &componentManager, EntityManager &entityManager)
    {
        if ((int)(sprite.getX() + animation.getRectWidth()) < 0) {
            componentManager.killEntity(this->_id);
            entityManager.killEntity(this->_id);
            return true;
        }
        return false;
    }

    bool ScalingBossEnemy::handle(const int64_t &time, ComponentManager &componentManager, EntityManager &entityManager, const size_t &windowWidth, const size_t &windowHeight)
    {
        entity_t player_id = entityManager.getEntitiesFromFamily("player")[0]->getId();
        Sprite &player_sprite = componentManager.get<Sprite>(player_id);
        Movement &movement = componentManager.get<Movement>(this->_id);
        Sprite &sprite = componentManager.get<Sprite>(this->_id);
        Animation &animation = componentManager.get<Animation>(this->_id);

        if (destroy(sprite, animation, componentManager, entityManager))
            return true;
        move(player_sprite, sprite, movement, animation, windowWidth, windowHeight);
        return false;
    }
}