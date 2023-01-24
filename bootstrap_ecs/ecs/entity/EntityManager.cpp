/*
** EPITECH PROJECT, 2023
** EntityManager
** File description:
** EntityManager
*/

#include "EntityManager.hpp"

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{

}

std::shared_ptr<Entity> EntityManager::spawn_entity(const std::string &family = "")
{
    std::shared_ptr<Entity> new_entity(new Entity());

    new_entity->set_family(family);
    for (auto &entity : _entities) {
        if (entity->get_status() == Entity::EntityStatus::DEAD) {
            new_entity->set_id(entity->get_id());
            entity->set_status(Entity::EntityStatus::USED);
            return new_entity;
        }
    }
    if (_entities.size() == 0)
        new_entity->set_id(0);
    else
        new_entity->set_id(_entities.back()->get_id() + 1);
    return new_entity;
}

const std::vector<std::shared_ptr<Entity>> &EntityManager::getEntities() const
{
    return _entities;
}

std::vector<std::shared_ptr<Entity>> EntityManager::getEntitiesFromFamily(const std::string &family) const
{
    std::vector<std::shared_ptr<Entity>> family_entities;

    for (auto &entity : _entities) {
        if (family == entity->get_family())
            family_entities.push_back(entity);
    }
    return family_entities;
}