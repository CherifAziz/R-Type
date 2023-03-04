/*
** EPITECH PROJECT, 2023
** EnemyManager.cpp
** File description:
** enemymanager's methode
*/

#include "EnemyManager.hpp"

#include "Collision.hpp"
#include "Text.hpp"

#include "GameValues.hpp"

#include "FlyEnemy.hpp"
#include "BasicEnemy.hpp"
#include "BossEnemy.hpp"
#include "VesselEnemy.hpp"
#include "MediumEnemy.hpp"

namespace rtype
{
    EnemyManager::EnemyManager()
    {
    }

    EnemyManager::~EnemyManager()
    {
    }

    std::shared_ptr<IEnemy> EnemyManager::createEnemy(std::string &enemy, ComponentManager &componentManager, EntityManager &entityManager)
    {
        std::shared_ptr<IEnemy> new_enemy;
        std::vector<std::shared_ptr<Entity>> enemies = entityManager.getEntitiesFromFamily(enemy);

        if (enemies.size() == ENEMY_LIMITER.at(enemy))
            return nullptr;
        if (enemy == "basicEnemy")
            new_enemy = std::make_shared<BasicEnemy>(componentManager, entityManager);
        else if (enemy == "mediumEnemy")
            new_enemy = std::make_shared<MediumEnemy>(componentManager, entityManager);
        else if (enemy == "flyEnemy")
            new_enemy = std::make_shared<FlyEnemy>(componentManager, entityManager);
        else if (enemy == "vesselEnemy")
            new_enemy = std::make_shared<VesselEnemy>(componentManager, entityManager);
        else if (enemy == "bossEnemy")
            new_enemy = std::make_shared<BossEnemy>(componentManager, entityManager);
        else
            throw std::invalid_argument("The given enemy does not exist: " + enemy);
        this->_enemies.push_back(new_enemy);
        return new_enemy;
    }

    void EnemyManager::handleEnemies(const int64_t &time, ComponentManager &componentManager, EntityManager &entityManager)
    {
        for (auto &enemy : this->_enemies) {
            if (entityManager.getEntityStatus(enemy->getId()) != Entity::EntityStatus::ALIVE || enemy->handle(time, componentManager, entityManager)) {
                _enemies.erase(std::find(_enemies.begin(), _enemies.end(), enemy));
                return handleEnemies(time, componentManager, entityManager);
            }
        }
    }
}