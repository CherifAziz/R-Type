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
         * @brief the ComponentManager to manager every component maps
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
             * @param entity 
             */
            void killEntity(unsigned long entity)
            {
                for (auto &components : _components)
                    (components.second)->deleteEntityComponents(entity);
            }

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
                    std::cerr << "component map has already been registered" << std::endl;
                }
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
