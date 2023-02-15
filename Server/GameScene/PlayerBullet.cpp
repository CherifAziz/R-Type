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
    const std::string GameScene::ENEMIES[] = {
        "basicEnemy"
    };

    const std::string GameScene::BULLET_NAMES[] = {
        "bullet",
        "chargedbullet",
        "bigbullet",
        "superbullet",
        "megabullet",
        "beboubullet"
    };

    void GameScene::handleBulletSpriteSheet(Animation &bullet)
    {
        std::shared_ptr<ComponentMap<Animation>> animationMap = _componentManager.getComponents<Animation>();
        entity_t entity_id = 0;

        if (animationMap->contains(bullet) == false)
            return;
        entity_id = animationMap->getEntityId(bullet);
        if (_bullet_sent[entity_id].first != BulletSentState::LONG_DISTANCE && _bullet_sent[entity_id].first != BulletSentState::SHOOTED)
            _bullet_sent[entity_id].first = (BulletSentState)((int)_bullet_sent[entity_id].first + 1);
        else if (_bullet_sent[entity_id].first == BulletSentState::LONG_DISTANCE) {
            _bullet_sent[entity_id].first = BulletSentState::SHOOTED;
            bullet.setRectWidth(bullet_frames.at(_bullet_sent[entity_id].second).second.width);
            bullet.setRectHeight(bullet_frames.at(_bullet_sent[entity_id].second).second.height);
            bullet.setX(bullet_frames.at(_bullet_sent[entity_id].second).second.x);
            bullet.setY(bullet_frames.at(_bullet_sent[entity_id].second).second.y);
        }
    }

    bool GameScene::handleBulletDestruction(Sprite &bullet, const size_t &windowWidth, entity_t entity)
    {
        int value = handleElementCollision(entity);

        if (value != -1) {
            // TEMPORARY, UNTIL ENTITIES DEATH ARE FIX
            Sprite &sprite = _componentManager.get<Sprite>(value);
            sprite.setPosition(2000, rand() % 900);
            //_componentManager.killEntity(value);
            //_entityManager.killEntity(value);
        }
        if (bullet.getX() >= (int)windowWidth || value != -1) {
            _componentManager.killEntity(entity);
            _entityManager.killEntity(entity);
            _bullet_sent.erase(entity);
            return true;
        }
        return false;
    }

    void GameScene::initBullet(entity_t entity)
    {
        Sprite &player_sprite = _componentManager.get<Sprite>(_entityManager.getEntitiesFromFamily("player")[0]->getId());
        Sound pow("assets/pow.ogg", false, Sound::SoundStatus::PLAY);
        Collision collision(std::vector<std::string>{"basicEnemy"}); // NEED TO BE CHANGED TO THE ENEMY VECTOR
        Sprite sprite("assets/spaceship.gif", player_sprite.getX() + PLAYER_SPRITE_WIDTH, player_sprite.getY() + (PLAYER_SPRITE_HEIGHT / 2), 4);
        Movement movement(20, 0);
        Animation animation(bullet_frames.at(_bulletLoad).first.width, bullet_frames.at(_bulletLoad).first.height, bullet_frames.at(_bulletLoad).first.x, bullet_frames.at(_bulletLoad).first.y, 1, 1, 0, 0, 500);

        if (_bulletLoad == BulletLoadState::BEBOU_CHARGE || _bulletLoad == BulletLoadState::MEGA_CHARGE)
            movement.setDirection(40, 0);
        else if (_bulletLoad == BulletLoadState::SUPER_CHARGE || _bulletLoad == BulletLoadState::BIG_CHARGE)
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
        Sprite &loading_sprite = _componentManager.get<Sprite>(_entityManager.getEntitiesFromFamily("loading")[0]->getId());

        loading_sprite.setPosition(player_sprite.getX() + PLAYER_SPRITE_WIDTH, player_sprite.getY() + (PLAYER_SPRITE_HEIGHT / 2));
    }

    void GameScene::initBulletLoading()
    {
        entity_t entity = _entityManager.spawnEntity("loading")->getId();
        Sprite &player_sprite = _componentManager.get<Sprite>(_entityManager.getEntitiesFromFamily("player")[0]->getId());
        Animation animation(31, 32, 2, 51, 8, 1, 1, 0, 500);
        Sprite sprite("assets/spaceship.gif", player_sprite.getX() + PLAYER_SPRITE_WIDTH, player_sprite.getY() + (PLAYER_SPRITE_HEIGHT / 2), 4);

        _componentManager.put<Animation>(animation, entity);
        _componentManager.put<Sprite>(sprite, entity);
    }

    void GameScene::spawnBullet(Action &player_action, const Action::KeyState &space_state)
    {
        // if (_loadState == LoadState::ON) {
            // initBulletLoading();
            // _loadState = LoadState::OFF;
        // }
        if (space_state == Action::KeyState::RELEASED) {
            std::shared_ptr<Entity> bullet = _entityManager.spawnEntity(BULLET_NAMES[(int)_bulletLoad]);
            initBullet(bullet->getId());
            _bullet_sent[bullet->getId()] = std::make_pair(BulletSentState::SENT, _bulletLoad);
            _bulletLoad = BulletLoadState::LITTLE;
            _bulletTime = BulletTimeState::NONE;
            player_action.setState(Action::KeyType::SPACE, Action::KeyState::UP);
            std::cout << "BULLET SENT" << std::endl;
            // entity_t entity = _entityManager.getEntitiesFromFamily("loading")[0]->getId();
            // _componentManager.killEntity(entity);
            // _entityManager.killEntity(entity);
            // _loadState = LoadState::ON;
        } else if (_bulletLoad != BulletLoadState::BEBOU_CHARGE) {
            _bulletTime = (BulletTimeState)((int)_bulletTime + 1);
            if (_bulletTime == BulletTimeState::READY) {
                _bulletTime = BulletTimeState::NONE;
                _bulletLoad = (BulletLoadState)((int)_bulletLoad + 1);
            }
        }
    }

    void GameScene::moveBullet(Sprite &bullet, const Movement &bullet_velocity)
    {
        std::cout << "X " << bullet.getX() << std::endl;
        bullet.setPosition(bullet.getX() + bullet_velocity.getXDirection(), bullet.getY());
    }

    void GameScene::handleBullet(const int64_t &time, Action &player_action, const size_t &windowWidth)
    {
        std::vector<std::shared_ptr<Entity>> bullets = _entityManager.getEntitiesFromSubFamily("bullet");
        std::shared_ptr<ComponentMap<Sprite>> spriteMap = _componentManager.getComponents<Sprite>();
        std::shared_ptr<ComponentMap<Animation>> animationMap = _componentManager.getComponents<Animation>();
        std::shared_ptr<ComponentMap<Movement>> movementMap = _componentManager.getComponents<Movement>();
        Action::KeyState space_state = player_action.getKeyState(Action::KeyType::SPACE);

        for (auto &bullet : bullets) {
            if (spriteMap->contains(bullet->getId())) {
                if (handleBulletDestruction(spriteMap->get(bullet->getId()), windowWidth, bullet->getId()))
                    return (handleBullet(time, player_action, windowWidth));
            }
        }
        // std::cout << "START " << bullets.size() << std::endl;
        // for (size_t it = 0; it < bullets.size(); it++)
        //     std::cout << bullets[it]->getId() << std::endl;
        // std::cout << "AFTER" << std::endl;
        for (auto &bullet : bullets) {
            if (animationMap->contains(bullet->getId()))
                handleBulletSpriteSheet(animationMap->get(bullet->getId()));
            // std::cout << "ID " << bullet->getId() << " ";
            if (movementMap->contains(bullet->getId()))
                moveBullet(spriteMap->get(bullet->getId()), movementMap->get(bullet->getId()));
        }
        // std::cout << "END" << std::endl;
        if (space_state != Action::KeyState::UP && time % 10 == 0) {
            spawnBullet(player_action, space_state);
            // if (_loadState == LoadState::OFF)
                // updateBulletLoading();
        }
    }
}