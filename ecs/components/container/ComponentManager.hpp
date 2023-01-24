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

    #include "Entity.hpp"
    #include "ComponentMap.hpp"

    class ComponentManager {
    public:
        ComponentManager()
        {
        }

        ~ComponentManager()
        {
        }

        void kill_entity(unsigned long entity)
        {
            for (auto &components : _components)
                (components.second)->delete_entity_components(entity);
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
        void remove_components(unsigned long entity)
        {
            (_components[std::type_index(typeid(Component))])->delete_entity_components(entity);
        }

        private:
        enum class EntityStatus {
            ALIVE,
            DEAD,
            USED
        };

        std::unordered_map<std::type_index, std::shared_ptr<IComponentMap>> _components;
};

#endif /* !ComponentManager */
