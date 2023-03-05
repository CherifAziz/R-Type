/*
** EPITECH PROJECT, 2023
** EnemyBullet
** File description:
** EnemyBullet
*/

#include "config.hpp"
#include "GameScene.hpp"
#include "GameValues.hpp"

#include "Collision.hpp"
#include <cmath>


namespace rtype {
    bool GameScene::handleEnemyBulletDestruction(Sprite &bullet, entity_t entity)
    {
        int value = handleElementCollision(entity);
        
        if (value != -1 && _playerShield == false) {
            _player_hp -= 1;
            if (_player_hp == 0) {
                std::cout << "THE END" << std::endl;
                exit(0);
            }
        }
        if (bullet.getX() <= 0) {
            _componentManager.killEntity(entity);
            _entityManager.killEntity(entity);
            _bullet_sent.erase(entity);
            return true;
        }
        return false;
    }

    void GameScene::callEnemiesSendingBullets(Sprite &player_sprite)
    {
        std::vector<std::shared_ptr<Entity>> vesselEnemies = _entityManager.getEntitiesFromFamily("vesselEnemy");
        std::vector<std::shared_ptr<Entity>> bossEnemies = _entityManager.getEntitiesFromFamily("bossEnemy");

        spawnEnemyBullet(vesselEnemies);
        spawnBossBullet(bossEnemies, player_sprite);
    }

    void GameScene::spawnBossBullet(std::vector<std::shared_ptr<Entity>> &enemies, Sprite &player_sprite)
    {
        std::shared_ptr<ComponentMap<Sprite>> spriteMap = _componentManager.getComponents<Sprite>();
        std::shared_ptr<ComponentMap<Animation>> animationMap = _componentManager.getComponents<Animation>();
        Collision collision({"player"});
        Animation animation(6, 6, 212, 279, 1, 1, 0, 0, 500);
        

        for (auto &shootEnemy : enemies) {
            entity_t bullet_id = _entityManager.spawnEntity("enemy_shoot")->getId();
            Sprite &enemy_sprite = spriteMap->get(shootEnemy->getId());
            Animation &enemy_animation = animationMap->get(shootEnemy->getId());
            Sprite sprite(std::string(ASSETS_DIR)+"spaceship.gif", enemy_sprite.getX() - 200 + (enemy_animation.getRectWidth() - 200) * enemy_sprite.getScale(), enemy_sprite.getY() - 75 + ((enemy_animation.getRectHeight() - 75) * enemy_sprite.getScale()) / 2 - bullet_frames.at(_bulletLoad).first.height, 4);
            float dx = (player_sprite.getX() + 15) - enemy_sprite.getX();
            float dy = player_sprite.getY() - enemy_sprite.getY();
            float direction = std::atan2(dy, dx);
            float distance = std::sqrt(dx*dx + dy*dy);
            float magnitude = distance * 0.01;
            Movement movement(std::cos(direction) * magnitude, (std::sin(direction) ) * magnitude);
            // std::cout << "y = " << (std::sin(direction) ) * magnitude << std::endl;
            // std::cout << "x = " << std::cos(direction) * magnitude << std::endl;
            // std::cout << "distance = " << distance << std::endl;
            // std::cout << "magnitude = " << magnitude << std::endl;
            // std::cout << "direction = " << direction << std::endl;

            _componentManager.put<Sprite>(sprite, bullet_id);
            _componentManager.put<Collision>(collision, bullet_id);
            _componentManager.put<Movement>(movement, bullet_id);
            _componentManager.put<Animation>(animation, bullet_id);
        }
    }

    void GameScene::spawnEnemyBullet(std::vector<std::shared_ptr<Entity>> &enemies)
    {
        std::shared_ptr<ComponentMap<Sprite>> spriteMap = _componentManager.getComponents<Sprite>();
        std::shared_ptr<ComponentMap<Animation>> animationMap = _componentManager.getComponents<Animation>();
        Collision collision({"player"});
        Movement movement(-10, 0);
        Animation animation(6, 6, 212, 279, 1, 1, 0, 0, 500);

        for (auto &shootEnemy : enemies) {
            entity_t bullet_id = _entityManager.spawnEntity("enemy_shoot")->getId();
            Sprite &enemy_sprite = spriteMap->get(shootEnemy->getId());
            Animation &enemy_animation = animationMap->get(shootEnemy->getId());
            Sprite sprite(std::string(ASSETS_DIR)+"spaceship.gif", enemy_sprite.getX() - 63 + (enemy_animation.getRectWidth() - 63) * enemy_sprite.getScale(), enemy_sprite.getY() + (enemy_animation.getRectHeight() * enemy_sprite.getScale()) / 2 - bullet_frames.at(_bulletLoad).first.height, 4);

            _componentManager.put<Sprite>(sprite, bullet_id);
            _componentManager.put<Collision>(collision, bullet_id);
            _componentManager.put<Movement>(movement, bullet_id);
            _componentManager.put<Animation>(animation, bullet_id);
        }
    }

    void GameScene::moveEnemyBullet(Sprite &bullet, const Movement &bullet_velocity)
    {
        bullet.setPosition(bullet.getX() + bullet_velocity.getXDirection(), bullet.getY() + bullet_velocity.getYDirection());
    }

    void GameScene::handleEnemyBullet(const int64_t &time)
    {
        std::vector<std::shared_ptr<Entity>> bullets = _entityManager.getEntitiesFromFamily("enemy_shoot");
        std::shared_ptr<ComponentMap<Sprite>> spriteMap = _componentManager.getComponents<Sprite>();
        std::shared_ptr<ComponentMap<Animation>> animationMap = _componentManager.getComponents<Animation>();
        std::shared_ptr<ComponentMap<Movement>> movementMap = _componentManager.getComponents<Movement>();

        for (auto &bullet : bullets) {
            if (spriteMap->contains(bullet->getId())) {
                if (handleEnemyBulletDestruction(spriteMap->get(bullet->getId()), bullet->getId()))
                    return (handleEnemyBullet(time));
            }
            if (movementMap->contains(bullet->getId()))
                moveEnemyBullet(spriteMap->get(bullet->getId()), movementMap->get(bullet->getId()));
        }
    }
}