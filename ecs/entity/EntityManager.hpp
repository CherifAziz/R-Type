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
                EntityManager();

                /**
                 * @brief Destroy the Entity Manager object
                 * 
                 */
                ~EntityManager();

                /**
                 * @brief generate a new entity
                 * 
                 * @details create a new entity, it's id and give him his family. If their are available id, the new entity will take them. If not, a new id will be generated
                 * @param family the family of the new entity. It help the Game System knowing how to handle the entity
                 * @return the new entity as a std::shared_ptr<Entity> 
                 */
                std::shared_ptr<Entity> spawnEntity(const std::string &family);

                /**
                 * @brief Get the Entity object
                 * 
                 * @param id the id of the entity to get
                 * @return the entity as a const std::shared_ptr<Entity>& 
                 */
                const std::shared_ptr<Entity> &getEntity(const entity_t &id) const;

                /**
                 * @brief Get the Entity Status object
                 * 
                 * @param id the id of the entity to get the status from
                 * @return the entity status as a const Entity::EntityStatus&
                 */
                const Entity::EntityStatus &getEntityStatus(const entity_t &id) const;

                /**
                 * @brief Kill entity by setting is status to dead
                 * 
                 * @param entity_id the entity to kill
                 */
                void killEntity(entity_t entity_id);

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
                std::vector<std::shared_ptr<Entity>> getEntitiesFromSubFamily(const std::string &family) const;

                /**
                 * @brief Get all the Entities object of a given family
                 * 
                 * @param family the family you want to get the entities from
                 * @return a vector of all entities coming from the given family as a std::vector<std::shared_ptr<Entity>> 
                 */
                std::vector<std::shared_ptr<Entity>> getEntitiesFromFamily(const std::string &family) const;

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
