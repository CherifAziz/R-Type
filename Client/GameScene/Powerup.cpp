/*
** EPITECH PROJECT, 2023
** Powerup
** File description:
** Powerup
*/

#include "GameScene.hpp"

namespace rtype {
    void GameScene::initPowerUp(const int &x, const int &y)
    {
        entity_t entity = _entityManager.spawnEntity("powerup_object")->getId();
        Sprite sprite("assets/object.gif", x, y, 4);
        Movement movement(-5, 0);
        Animation animation(16, 16, 197, 216, 4, 1, 1, 0, 500);

        _componentManager.put<Sprite>(sprite, entity);
        _componentManager.put<Animation>(animation, entity);
        _componentManager.put<Movement>(movement, entity);
    }

    void GameScene::movePowerUp(Sprite &object, const Movement &object_movement)
    {
        object.setPosition(object.getX() + object_movement.getXDirection(), object.getY());
    }

    void GameScene::changePlayerSprite(const bool &shieldStatus, const int64_t &time)
    {
        entity_t player_id = _entityManager.getEntitiesFromFamily("player")[0]->getId();
        Sprite &player_sprite = _componentManager.get<Sprite>(player_id);
        Animation &player_animation = _componentManager.get<Animation>(player_id);

        _playerShield = shieldStatus;
        if (shieldStatus) {
            player_animation.setVerticalPictureNb(5);
            handleGameTime(SHIELD_TIME, time, "powerUp");
            _laps["powerUp"].lastTime = 0;
            _laps["powerUp"].lapsPassed = 1;
        } else {
            player_animation.setVerticalPictureNb(1);
            player_animation.setY(2);
        }
    }

    bool GameScene::checkPlayerGettingPowerUp(const entity_t &entity, Sprite &object, Animation &object_animation, const int64_t &time)
    {
        entity_t player_entity = _entityManager.getEntitiesFromFamily("player")[0]->getId();
        Sprite &player_sprite = _componentManager.get<Sprite>(player_entity);
        Animation &player_animation = _componentManager.get<Animation>(player_entity);

        if (isColliding(object.getX(), object.getY(), object_animation.getRectWidth() * object.getScale(), object_animation.getRectHeight() * object.getScale(),
            player_sprite.getX(), player_sprite.getY(), player_animation.getRectWidth() * player_sprite.getScale(), player_animation.getRectHeight() * player_sprite.getScale())) {
            _componentManager.killEntity(entity);
            _entityManager.killEntity(entity);
            changePlayerSprite(true, time);
            return true;
        }
        return false;
    }

    void GameScene::handlePowerUp(const int64_t &time)
    {
        std::vector<std::shared_ptr<Entity>> powerup_objects = _entityManager.getEntitiesFromSubFamily("powerup_object");

        if (_playerShield == true) {
            if (handleGameTime(SHIELD_TIME, time, "powerUp"))
                changePlayerSprite(false, time);
        }
        for (auto &object : powerup_objects) {
            if (checkPlayerGettingPowerUp(object->getId(), _componentManager.get<Sprite>(object->getId()), _componentManager.get<Animation>(object->getId()), time))
                return;
            movePowerUp(_componentManager.get<Sprite>(object->getId()), _componentManager.get<Movement>(object->getId()));
        }
    }
}