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
#include "Serialize.hpp"
#include "Services.hpp"
#include "Network.hpp"

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

    std::shared_ptr<IEnemy> EnemyManager::createEnemy(EnemyType type, ComponentManager &componentManager, EntityManager &entityManager)
    {
        std::shared_ptr<IEnemy> new_enemy;
        std::vector<std::shared_ptr<Entity>> enemies = entityManager.getEntitiesFromFamily(enemyTranslator.at(type));
        std::vector<std::shared_ptr<rtype::Entity>> players = entityManager.getEntitiesFromFamily("player");


        if (enemies.size() == enemyLimiter.at(type))
            return nullptr;
        switch (type) {
            case EnemyType::BASIC:
                new_enemy = std::make_shared<BasicEnemy>(componentManager, entityManager);
                break;
            case EnemyType::FLY:
                new_enemy = std::make_shared<FlyEnemy>(componentManager, entityManager);
                break;
            case EnemyType::BOSS:
                new_enemy = std::make_shared<BossEnemy>(componentManager, entityManager);
                break;
            case EnemyType::MEDIUM:
                new_enemy = std::make_shared<MediumEnemy>(componentManager, entityManager);
                break;
            case EnemyType::VESSEL:
                new_enemy = std::make_shared<VesselEnemy>(componentManager, entityManager);
                break;
            default:
                break;
        }
        this->_enemies.push_back(new_enemy);
        std::cout << "macron demission" << std::endl;
        for (auto &player: players) {
            std::cout << "zemmour" << std::endl;
            componentManager.get<rtype::Network>(player->getId()).addToQueue(Serialize::createData<Serialize::Data>(Services::Command::NEW_ENEMY, {std::to_string(type), std::to_string(new_enemy->getPos().first), std::to_string(new_enemy->getPos().second)}));
            std::cout << "zemmour president !!!" << std::endl;
        }
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