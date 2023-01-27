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
            EntityManager();
            ~EntityManager();

            std::shared_ptr<Entity> spawnEntity(const std::string &family);
            const std::vector<std::shared_ptr<Entity>> &getEntities() const;
            std::vector<std::shared_ptr<Entity>> getEntitiesFromFamily(const std::string &family) const;
        private:
            std::vector<std::shared_ptr<Entity>> _entities;
    };

#endif /* !EntityManager */
