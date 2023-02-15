/*
** EPITECH PROJECT, 2023
** EntityManager
** File description:
** EntityManager
*/

#ifndef EntityManagerDef
    #define EntityManagerDef

    #include <vector>
    #include <memory>

    #include "Entity.hpp"

    namespace rtype {
        /**
         * @brief this class Manage every entities of the RType
         * 
         */
        class EntityManager {
            public:
                /**
                 * @brief Construct a new Entity Manager object
                 * 
                 */
                EntityManager() = default;

                /**
                 * @brief Destroy the Entity Manager object
                 * 
                 */
                ~EntityManager() = default;

                /**
                 * @brief generate a new entity
                 * 
                 * @details create a new entity, it's id and give him his family. If their are available id, the new entity will take them. If not, a new id will be generated
                 * @param family the family of the new entity. It help the Game System knowing how to handle the entity
                 * @return the new entity as a std::shared_ptr<Entity> 
                 */
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
                    new_entity->setId(_biggestId);
                    _biggestId += 1;
                    _entities.push_back(new_entity);
                    return new_entity;
                }

                /**
                 * @brief Kill entity by setting is status to dead
                 * 
                 * @param entity_id the entity to kill
                 */
                void killEntity(entity_t entity_id)
                {
                    for (auto &entity : _entities) {
                        if (entity->getId() == entity_id && entity->getStatus() == Entity::EntityStatus::ALIVE) {
                            entity->setStatus(Entity::EntityStatus::DEAD);
                            return;
                        }
                    }
                    throw std::invalid_argument("Entity not found in killEntity method !");
                }

                /**
                 * @brief Get all the Entities object
                 * 
                 * @return a vector of all entities as a const std::vector<std::shared_ptr<Entity>>& 
                 */
                const std::vector<std::shared_ptr<Entity>> &getEntities() const
                {
                    return _entities;
                }

                /**
                 * @brief Get all the Entities object of a given substring family
                 * 
                 * @param family the substring family you want to get the entities from
                 * @return a vector of all entities coming from the given substring family as a std::vector<std::shared_ptr<Entity>> 
                 */
                std::vector<std::shared_ptr<Entity>> getEntitiesFromSubFamily(const std::string &family) const
                {
                    std::vector<std::shared_ptr<Entity>> family_entities;

                    for (auto &entity : _entities) {
                        if (entity->getFamily().find(family) != std::string::npos && entity->getStatus() == Entity::EntityStatus::ALIVE) {
                            family_entities.push_back(entity);
                        }
                    }
                    return family_entities;
                }

                /**
                 * @brief Get all the Entities object of a given family
                 * 
                 * @param family the family you want to get the entities from
                 * @return a vector of all entities coming from the given family as a std::vector<std::shared_ptr<Entity>> 
                 */
                std::vector<std::shared_ptr<Entity>> getEntitiesFromFamily(const std::string &family) const
                {
                    std::vector<std::shared_ptr<Entity>> family_entities;

                    for (auto &entity : _entities) {
                        if (family == entity->getFamily() && entity->getStatus() == Entity::EntityStatus::ALIVE)
                            family_entities.push_back(entity);
                    }
                    return family_entities;
                }

            protected:
                /**
                 * @brief the entities
                 * 
                 */
                std::vector<std::shared_ptr<Entity>> _entities;

                /**
                 * @brief boolean to check if the game is still playing
                 * 
                 */
                bool _gamePlaying = true;

                /**
                 * @brief the biggest Id given until now
                 * 
                 */
                size_t _biggestId = 0;
        };
    }

#endif /* !EntityManagerDef */
