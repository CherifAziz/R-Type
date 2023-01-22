/*
** EPITECH PROJECT, 2023
** ComponentManager
** File description:
** ComponentManager
*/

#ifndef ComponentManager
    #define _ComponentManager_

    #include <typeindex>
    #include <memory>
    #include <unordered_map>
    #include <map>

    #include "ComponentMap.hpp"

    class ComponentManager {
    public:
        ComponentManager()
        {
        }

        ~ComponentManager()
        {
        }

        entity_t spawn_entity()
        {
            entity_t new_entity;

            for (auto &entity : _entity_status) {
                if (entity.second == EntityStatus::DEAD) {
                    new_entity = entity.first;
                    entity.second = EntityStatus::USED;
                    _entity_status[new_entity] = EntityStatus::ALIVE;
                    return new_entity;
                }
            }
            if (_entity_status.size() == 0)
                new_entity = 0;
            else
                new_entity = (--_entity_status.end())->first + 1;
            _entity_status[new_entity] = EntityStatus::ALIVE;
            return new_entity;
        }

        void kill_entity(const entity_t &entity)
        {
            for (auto &components : _components)
                (components.second)->delete_entity_components(entity);
            _entity_status[entity] = EntityStatus::DEAD;
        }

        template <class Component>
        void register_component(ComponentMap<Component> new_component)
        {
            if (_components.count(std::type_index(typeid(Component))) == 0) {
                _components[std::type_index(typeid(Component))] = std::make_shared<ComponentMap<Component>>(new_component);
            } else {
                std::cerr << "component map has already been registered" << std::endl;
            }
        }

        template <class Component>
        std::shared_ptr<ComponentMap<Component>> get_components()
        {
            return std::static_pointer_cast<ComponentMap<Component>>(_components[std::type_index(typeid(Component))]);
        }

        template <class Component>
        void remove_components(const entity_t &entity)
        {
            (_components[std::type_index(typeid(Component))])->delete_entity_components(entity);
        }

        private:
        enum class EntityStatus {
            ALIVE,
            DEAD,
            USED
        };

        std::map<entity_t, EntityStatus> _entity_status;
        std::unordered_map<std::type_index, std::shared_ptr<IComponentMap>> _components;
};

#endif /* !ComponentManager */
