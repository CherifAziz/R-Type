/*
** EPITECH PROJECT, 2023
** EntityManager
** File description:
** EntityManager
*/

#ifndef EntityManager
    #define _EntityManager_

    #include <vector>
    #include <memory>

    #include "Entity.hpp"

    class EntityManager {
        public:
            EntityManager() = default;
            ~EntityManager() = default;

            std::shared_ptr<Entity> spawnEntity(const std::string &family)
            {
                std::shared_ptr<Entity> new_entity(new Entity());

                new_entity->setFamily(family);
                for (auto &entity : _entities) {
                    if (entity->getStatus() == Entity::EntityStatus::DEAD) {
                        new_entity->setId(entity->getId());
                        entity->setStatus(Entity::EntityStatus::USED);
                        _entities.push_back(new_entity);
                        return new_entity;
                    }
                }
                if (_entities.size() == 0)
                    new_entity->setId(0);
                else
                    new_entity->setId(_entities.back()->getId() + 1);
                _entities.push_back(new_entity);
                return new_entity;
            }

            const std::vector<std::shared_ptr<Entity>> &getEntities() const
            {
                return _entities;
            }

            std::vector<std::shared_ptr<Entity>> getEntitiesFromFamily(const std::string &family) const
            {
                std::vector<std::shared_ptr<Entity>> family_entities;

                for (auto &entity : _entities) {
                    if (family == entity->getFamily())
                        family_entities.push_back(entity);
                }
                return family_entities;
            }

        protected:
            std::vector<std::shared_ptr<Entity>> _entities;
    };

#endif /* !EntityManager */
