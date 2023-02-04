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
                    if (_entities.size() == 0)
                        new_entity->setId(0);
                    else
                        new_entity->setId(_entities.back()->getId() + 1);
                    _entities.push_back(new_entity);
                    return new_entity;
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
                 * @brief Get all the Entities object of a given family
                 * 
                 * @param family the family you want to get the entities from
                 * @return a vector of all entities coming from the given family as a std::vector<std::shared_ptr<Entity>> 
                 */
                std::vector<std::shared_ptr<Entity>> getEntitiesFromFamily(const std::string &family) const
                {
                    std::vector<std::shared_ptr<Entity>> family_entities;

                    for (auto &entity : _entities) {
                        if (family == entity->getFamily())
                            family_entities.push_back(entity);
                    }
                    return family_entities;
                }

                void setGamePlayingStatus(const bool &gamePlaying) { _gamePlaying = gamePlaying; }

                const bool &isGamePlaying() const { return _gamePlaying; }

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
        };
    }

#endif /* !EntityManagerDef */
