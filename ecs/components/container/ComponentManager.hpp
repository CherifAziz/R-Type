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

    namespace rtype {
        class ComponentManager {
        public:
            ComponentManager()
            {
            }

            ~ComponentManager()
            {
            }

            void killEntity(unsigned long entity)
            {
                for (auto &components : _components)
                    (components.second)->deleteEntityComponents(entity);
            }

            template <class Component>
            void registerComponent(ComponentMap<Component> new_component)
            {
                if (_components.count(std::type_index(typeid(Component))) == 0) {
                    _components[std::type_index(typeid(Component))] = std::make_shared<ComponentMap<Component>>(new_component);
                } else {
                    std::cerr << "component map has already been registered" << std::endl;
                }
            }

            template <class Component>
            std::shared_ptr<ComponentMap<Component>> getComponents()
            {
                return std::static_pointer_cast<ComponentMap<Component>>(_components[std::type_index(typeid(Component))]);
            }

            template <class Component>
            void removeComponents(unsigned long entity)
            {
                (_components[std::type_index(typeid(Component))])->deleteEntityComponents(entity);
            }

            protected:
            std::unordered_map<std::type_index, std::shared_ptr<IComponentMap>> _components;
        };
    }

#endif /* !ComponentManager */
