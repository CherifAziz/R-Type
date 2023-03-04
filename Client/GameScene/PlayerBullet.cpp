/*
** EPITECH PROJECT, 2023
** PlayerBullet
** File description:
** PlayerBullet
*/

#include "GameScene.hpp"
#include "GameValues.hpp"

#include "Collision.hpp"

namespace rtype {
    const std::vector<std::string> GameScene::ENEMIES = {
        "basicEnemy",
        "mediumEnemy",
        "vesselEnemy",
        "flyEnemy",
        "boss"
    };

    const std::vector<std::string> GameScene::BULLET_NAMES = {
        "bullet",
        "chargedbullet",
        "bigbullet",
        "superbullet",
        "megabullet",
        "beboubullet"
    };

    void GameScene::handleBulletSpriteSheet(Animation &bullet, entity_t &player_id)
    {
        std::shared_ptr<ComponentMap<Animation>> animationMap = _componentManager.getComponents<Animation>();
        entity_t entity_id = 0;

        if (animationMap->contains(bullet) == false)
            return;
        entity_id = animationMap->getEntityId(bullet);
        if (_bullet_sent[player_id][entity_id].first != BulletSentState::LONG_DISTANCE && _bullet_sent[player_id][entity_id].first != BulletSentState::SHOOTED)
            _bullet_sent[player_id][entity_id].first = (BulletSentState)((int)_bullet_sent[player_id][entity_id].first + 1);
        else if (_bullet_sent[player_id][entity_id].first == BulletSentState::LONG_DISTANCE) {
            _bullet_sent[player_id][entity_id].first = BulletSentState::SHOOTED;
            bullet.setRectWidth(bullet_frames.at(_bullet_sent[player_id][entity_id].second).second.width);
            bullet.setRectHeight(bullet_frames.at(_bullet_sent[player_id][entity_id].second).second.height);
            bullet.setX(bullet_frames.at(_bullet_sent[player_id][entity_id].second).second.x);
            bullet.setY(bullet_frames.at(_bullet_sent[player_id][entity_id].second).second.y);
        }
    }

    bool GameScene::handleBulletDestruction(Sprite &bullet, const size_t &windowWidth, entity_t entity, entity_t &player_id)
    {
        const std::shared_ptr<Entity> _bullet = _entityManager.getEntity(entity);
        const std::string bullet_family = _bullet->getFamily();
        int value = handleElementCollision(entity);

        if (value != -1) {
            const std::string family = _entityManager.getEntity(value)->getFamily();

            _componentManager.killEntity(value);
            _entityManager.killEntity(value);
            auto& wave = waves[0];
            auto it = std::find_if(wave.begin(), wave.end(), [&](auto& p) {
                return p.first == family;
            });
            if (it != wave.end()) {
                if (it->second != 0)
                    --it->second;
            }
            if (family == "basicEnemy")
                _score += 10;
            if (family == "mediumEnemy")
                _score += 15;
            if (family == "flyEnemy")
                _score += 25;
            if (family == "vesselEnemy")
                _score += 20;
            if (bullet_family != "beboubullet") {
                _componentManager.killEntity(entity);
                _entityManager.killEntity(entity);
                _bullet_sent[player_id].erase(entity);
                return true;
            }
        }
        if (bullet.getX() >= (int)windowWidth) {
            _componentManager.killEntity(entity);
            _entityManager.killEntity(entity);
            _bullet_sent[player_id].erase(entity);
            return true;
        }
        return false;
    }

    void GameScene::initBullet(entity_t entity, entity_t player_id)
    {
        Sprite &player_sprite = _componentManager.get<Sprite>(player_id);
        Animation &player_animation = _componentManager.get<Animation>(player_id);
        Sound pow("assets/pow.ogg", false, Sound::SoundStatus::PLAY);
        Collision collision(ENEMIES);
        Sprite sprite("assets/spaceship.gif", player_sprite.getX() + player_animation.getRectWidth() * player_sprite.getScale(), player_sprite.getY() + (player_animation.getRectHeight() * player_sprite.getScale()) / 2 - bullet_frames.at(_bulletLoad[player_id]).first.height, 4);
        Movement movement(20, 0);
        Animation animation(bullet_frames.at(_bulletLoad[player_id]).first.width, bullet_frames.at(_bulletLoad[player_id]).first.height, bullet_frames.at(_bulletLoad[player_id]).first.x, bullet_frames.at(_bulletLoad[player_id]).first.y, 1, 1, 0, 0, 500);

        if (_bulletLoad[player_id] == BulletLoadState::BEBOU_CHARGE || _bulletLoad[player_id] == BulletLoadState::MEGA_CHARGE)
            movement.setDirection(40, 0);
        else if (_bulletLoad[player_id] == BulletLoadState::SUPER_CHARGE || _bulletLoad[player_id] == BulletLoadState::BIG_CHARGE)
            movement.setDirection(30, 0);
        _componentManager.put<Sound>(pow, entity);
        _componentManager.put<Sprite>(sprite, entity);
        _componentManager.put<Collision>(collision, entity);
        _componentManager.put<Movement>(movement, entity);
        _componentManager.put<Animation>(animation, entity);
    }

    void GameScene::updateBulletLoading()
    {
        Sprite &player_sprite = _componentManager.get<Sprite>(_entityManager.getEntitiesFromFamily("player")[0]->getId());
        Animation &player_animation = _componentManager.get<Animation>(_entityManager.getEntitiesFromFamily("player")[0]->getId());
        Sprite &loading_sprite = _componentManager.get<Sprite>(_entityManager.getEntitiesFromFamily("loading")[0]->getId());

        loading_sprite.setPosition(player_sprite.getX() + player_animation.getRectWidth() * player_sprite.getScale(), player_sprite.getY() - player_animation.getRectHeight() / 2);
    }

    void GameScene::initBulletLoading()
    {
        entity_t entity = _entityManager.spawnEntity("loading")->getId();
        Sprite &player_sprite = _componentManager.get<Sprite>(_entityManager.getEntitiesFromFamily("player")[0]->getId());
        Animation &player_animation = _componentManager.get<Animation>(_entityManager.getEntitiesFromFamily("player")[0]->getId());
        Animation animation(31, 32, 2, 51, 8, 1, 1, 0, 500);
        Sprite sprite("assets/spaceship.gif", player_sprite.getX() + player_animation.getRectWidth() * player_sprite.getScale(), player_sprite.getY() - player_animation.getRectHeight() / 2, 4);

        _componentManager.put<Animation>(animation, entity);
        _componentManager.put<Sprite>(sprite, entity);
    }

    void GameScene::spawnBullet(Action &player_action, const Action::KeyState &space_state, entity_t player)
    {
        if (_loadState.count(player) == 0 || _loadState[player] == LoadState::ON) {
            initBulletLoading();
            _loadState[player] = LoadState::OFF;
            _bulletLoad[player] = BulletLoadState::LITTLE;
        }
        if (space_state == Action::KeyState::RELEASED) {
            std::shared_ptr<Entity> bullet = _entityManager.spawnEntity(BULLET_NAMES[(int)_bulletLoad[player]]);
            initBullet(bullet->getId(), player);
            _bullet_sent[player][bullet->getId()] = std::make_pair(BulletSentState::SENT, _bulletLoad[player]);
            _bulletLoad[player] = BulletLoadState::LITTLE;
            _bulletTime[player] = BulletTimeState::NONE;
            player_action.setState(Action::KeyType::SPACE, Action::KeyState::UP);
            entity_t entity = _entityManager.getEntitiesFromFamily("loading")[0]->getId();
            _componentManager.killEntity(entity);
            _entityManager.killEntity(entity);
            _loadState[player] = LoadState::ON;
        } else if (_bulletLoad[player] != BulletLoadState::BEBOU_CHARGE) {
            if (_bulletTime.count(player) == 0)
                _bulletTime[player] = BulletTimeState::NONE;
            _bulletTime[player] = (BulletTimeState)((int)_bulletTime[player] + 1);
            if (_bulletTime[player] == BulletTimeState::READY) {
                _bulletTime[player] = BulletTimeState::NONE;
                _bulletLoad[player] = (BulletLoadState)((int)_bulletLoad[player] + 1);
            }
        }
    }

    void GameScene::moveBullet(Sprite &bullet, const Movement &bullet_velocity)
    {
        bullet.setPosition(bullet.getX() + bullet_velocity.getXDirection(), bullet.getY());
    }

    void GameScene::handleBullet(const int64_t &time, Action &player_action, const size_t &windowWidth, entity_t player_id)
    {
        std::vector<std::shared_ptr<Entity>> bullets = _entityManager.getEntitiesFromSubFamily("bullet");
        std::shared_ptr<ComponentMap<Sprite>> spriteMap = _componentManager.getComponents<Sprite>();
        std::shared_ptr<ComponentMap<Animation>> animationMap = _componentManager.getComponents<Animation>();
        std::shared_ptr<ComponentMap<Movement>> movementMap = _componentManager.getComponents<Movement>();
        Action::KeyState space_state = player_action.getKeyState(Action::KeyType::SPACE);

        for (auto &bullet : bullets) {
            if (spriteMap->contains(bullet->getId())) {
                if (handleBulletDestruction(spriteMap->get(bullet->getId()), windowWidth, bullet->getId(), player_id))
                    return (handleBullet(time, player_action, windowWidth, player_id));
            }
        }
        for (auto &bullet : bullets) {
            if (animationMap->contains(bullet->getId()))
                handleBulletSpriteSheet(animationMap->get(bullet->getId()), player_id);
            if (movementMap->contains(bullet->getId()))
                moveBullet(spriteMap->get(bullet->getId()), movementMap->get(bullet->getId()));
        }
        if (space_state != Action::KeyState::UP && time % 10 == 0) {
            spawnBullet(player_action, space_state, player_id);
            if (_loadState[player_id] == LoadState::OFF)
                updateBulletLoading();
        }
    }
}