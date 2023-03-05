/*
** EPITECH PROJECT, 2023
** ComponentManager
** File description:
** ComponentManager
*/

#include "ComponentManager.hpp"

namespace rtype {

    ComponentManager::ComponentManager()
    {
    }

    ComponentManager::~ComponentManager()
    {
    }

    void ComponentManager::killEntity(unsigned long entity)
    {
        for (auto &components : _components)
            (components.second)->deleteEntityComponents(entity);
    }
}