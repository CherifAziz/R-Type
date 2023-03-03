/*
** EPITECH PROJECT, 2023
** EnemyBullet
** File description:
** EnemyBullet
*/

#include "GameScene.hpp"
#include "GameValues.hpp"

#include "Collision.hpp"

namespace rtype {

    bool GameScene::handleEnemyBulletDestruction(Sprite &bullet, const size_t &windowWidth, entity_t entity)
    {
        int value = handleElementCollision(entity);
        
        if (value != -1) {
            _player_hp -= 1;
            if (_player_hp == 0) {
                std::cout << "THE END" << std::endl;
                exit(0);
            }
        }
        if (bullet.getX() >= (int)windowWidth) {
            _componentManager.killEntity(entity);
            _entityManager.killEntity(entity);
            _bullet_sent.erase(entity);
            return true;
        }
        return false;
    }

    void GameScene::spawnEnemyBullet(std::vector<std::shared_ptr<Entity>> &enemies)
    {
        std::shared_ptr<ComponentMap<Sprite>> spriteMap = _componentManager.getComponents<Sprite>();
        std::shared_ptr<ComponentMap<Animation>> animationMap = _componentManager.getComponents<Animation>();
        Collision collision({"player"});
        Movement movement(-10, 0);
        Animation animation(6, 6, 212, 279, 1, 1, 0, 0, 500);

        for (auto &shootEnemy : enemies) {
            std::shared_ptr<Entity> bullet = _entityManager.spawnEntity("enemy_shoot");
            entity_t bullet_id = bullet->getId();
            Sprite &enemy_sprite = spriteMap->get(shootEnemy->getId());
            Animation &enemy_animation = animationMap->get(shootEnemy->getId());
            Sprite sprite("assets/spaceship.gif", enemy_sprite.getX() - 63 + (enemy_animation.getRectWidth() - 63) * enemy_sprite.getScale(), enemy_sprite.getY() + (enemy_animation.getRectHeight() * enemy_sprite.getScale()) / 2 - bullet_frames.at(_bulletLoad).first.height, 4);

            _componentManager.put<Sprite>(sprite, bullet_id);
            _componentManager.put<Collision>(collision, bullet_id);
            _componentManager.put<Movement>(movement, bullet_id);
            _componentManager.put<Animation>(animation, bullet_id);
        }
    }

    void GameScene::moveEnemyBullet(Sprite &bullet, const Movement &bullet_velocity)
    {
        bullet.setPosition(bullet.getX() + bullet_velocity.getXDirection(), bullet.getY());
    }

    void GameScene::handleEnemyBullet(const int64_t &time, const size_t &windowWidth)
    {
        std::vector<std::shared_ptr<Entity>> bullets = _entityManager.getEntitiesFromFamily("enemy_shoot");
        std::shared_ptr<ComponentMap<Sprite>> spriteMap = _componentManager.getComponents<Sprite>();
        std::shared_ptr<ComponentMap<Animation>> animationMap = _componentManager.getComponents<Animation>();
        std::shared_ptr<ComponentMap<Movement>> movementMap = _componentManager.getComponents<Movement>();

        for (auto &bullet : bullets) {
            if (spriteMap->contains(bullet->getId())) {
                if (handleEnemyBulletDestruction(spriteMap->get(bullet->getId()), windowWidth, bullet->getId()))
                    return (handleEnemyBullet(time, windowWidth));
            }
            if (movementMap->contains(bullet->getId()))
                moveEnemyBullet(spriteMap->get(bullet->getId()), movementMap->get(bullet->getId()));
        }
    }
}