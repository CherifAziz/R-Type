/*
** EPITECH PROJECT, 2023
** ComponentManager
** File description:
** ComponentManager
*/

#ifndef ComponentManagerDef
    #define ComponentManagerDef

    #include <typeindex>
    #include <memory>
    #include <unordered_map>
    #include <map>

    #include "ComponentMap.hpp"

    namespace rtype {
        /**
         * @brief the ComponentManager to manage every component maps
         * 
         */
        class ComponentManager {
        public:
            /**
             * @brief Construct a new Component Manager object
             * 
             */
            ComponentManager() = default;

            /**
             * @brief Destroy the Component Manager object
             * 
             */
            ~ComponentManager() = default;

            /**
             * @brief kill the entity given by the entity id and delete all of his components
             * 
             * @param entity the entity to kill all components from
             */
            void killEntity(unsigned long entity);

            /**
             * @brief add new ComponentMap in the components map
             * 
             * @tparam Component the template of the type of Component stored in the ComponentMap
             * @param new_component the ComponentMap to add
             */
            template <class Component>
            void registerComponent(ComponentMap<Component> new_component)
            {
                if (_components.count(std::type_index(typeid(Component))) == 0) {
                    _components[std::type_index(typeid(Component))] = std::make_shared<ComponentMap<Component>>(new_component);
                } else {
                    throw std::runtime_error("component map has already been registered");
                }
            }

            /**
             * @brief add a new component in the ComponentMap of the templated type
             * 
             * @tparam Component the template of the ComponentMap to add the new component into
             * @param newComponent the new component to add
             */
            template <class Component>
            void put(Component &newComponent, entity_t &entity)
            {
                if (_components.count(std::type_index(typeid(Component))) == 0) {
                    ComponentMap<Component> map;
                    map.put(newComponent, entity);
                    registerComponent<Component>(map);
                } else {
                    std::shared_ptr<ComponentMap<Component>> map = getComponents<Component>();
                    map->put(newComponent, entity);
                }
            }

            /**
             * @brief Get templated component type of entity
             * 
             * @tparam Component the type of component
             * @param entity the entity id of the entity belonging to the component
             * @return Component& the component of the entity
             */
            template <class Component>
            Component &get(const entity_t &entity)
            {
                std::shared_ptr<ComponentMap<Component>> map = getComponents<Component>();

                return map->get(entity);
            }

            /**
             * @brief Get the ComponentMap of the templated component
             * 
             * @tparam Component the template of the type of Component stored in the ComponentMap
             * @return the ComponentMap of the templated component as a std::shared_ptr<ComponentMap<Component>>
             */
            template <class Component>
            std::shared_ptr<ComponentMap<Component>> getComponents()
            {
                return std::static_pointer_cast<ComponentMap<Component>>(_components[std::type_index(typeid(Component))]);
            }

            /**
             * @brief Remove the components of the entity parameter in the ComponentMap known with the template
             * 
             * @tparam Component the template of the type of Component stored in the ComponentMap
             * @param entity the id of the entity to removed the components from
             */
            template <class Component>
            void removeComponents(unsigned long entity)
            {
                (_components[std::type_index(typeid(Component))])->deleteEntityComponents(entity);
            }

            protected:
            /**
             * @brief the map to store all the ComponentMap with the type of component stored as key and the ComponentMap as value
             * 
             */
            std::unordered_map<std::type_index, std::shared_ptr<IComponentMap>> _components;
        };
    }

#endif /* !ComponentManager */
