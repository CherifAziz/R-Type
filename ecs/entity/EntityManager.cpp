/*
** EPITECH PROJECT, 2023
** EntityManager
** File description:
** EntityManager
*/

#include <iostream>
#include "EntityManager.hpp"

namespace rtype {

    EntityManager::EntityManager()
    {
    }

    EntityManager::~EntityManager()
    {
    }

    std::shared_ptr<Entity> EntityManager::spawnEntity(const std::string &family)
    {
        std::shared_ptr<Entity> new_entity(new Entity());

        new_entity->setFamily(family);
        new_entity->setId(_biggestId);
        _biggestId += 1;
        _entities.push_back(new_entity);
        return new_entity;
    }

    const std::shared_ptr<Entity> &EntityManager::getEntity(const entity_t &id) const
    {
        for (auto &entity : _entities)
            if (entity->getId() == id)
                return entity;
        throw std::invalid_argument("Entity id doesn't exist");
    }

    const Entity::EntityStatus &EntityManager::getEntityStatus(const entity_t &id) const
    {
        return getEntity(id)->getStatus();
    }

    void EntityManager::killEntity(entity_t entity_id)
    {
        for (auto &entity : _entities) {
            if (entity->getId() == entity_id && entity->getStatus() == Entity::EntityStatus::ALIVE) {
                entity->setStatus(Entity::EntityStatus::DEAD);
                entity->hide();
                return;
            }
        }
        std::cout << "Entity: " << entity_id << " " << (int)getEntity(entity_id)->getStatus() << " " << getEntity(entity_id)->getFamily() << std::endl;
        throw std::invalid_argument("Entity not found in killEntity method !");
    }

    std::vector<std::shared_ptr<Entity>> EntityManager::getEntitiesFromSubFamily(const std::string &family) const
    {
        std::vector<std::shared_ptr<Entity>> family_entities;

        for (auto &entity : _entities) {
            if (entity->getFamily().find(family) != std::string::npos && entity->getStatus() == Entity::EntityStatus::ALIVE) {
                family_entities.push_back(entity);
            }
        }
        return family_entities;
    }

    std::vector<std::shared_ptr<Entity>> EntityManager::getEntitiesFromFamily(const std::string &family) const
    {
        std::vector<std::shared_ptr<Entity>> family_entities;

        for (auto &entity : _entities) {
            if (family == entity->getFamily() && entity->getStatus() == Entity::EntityStatus::ALIVE)
                family_entities.push_back(entity);
        }
        return family_entities;
    }
}