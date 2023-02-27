/*
** EPITECH PROJECT, 2023
** ComponentMap
** File description:
** ComponentMap
*/

#ifndef ComponentMapDef
    #define ComponentMapDef

    #include <unordered_map>
    #include <algorithm>
    #include <iostream>

    #include "Entity.hpp"
    #include "Network.hpp"

    #include "IComponentMap.hpp"

    namespace rtype {
        /**
         * @brief the ComponentMap to stock every components of a Component type
         *
         * @tparam Component the Component type of the ComponentMap
         */
        template <typename Component>
        class ComponentMap : public IComponentMap
        {
            public:
                /**
                 * @brief Construct a new Component Map object
                 *
                 */
                ComponentMap() = default;

                /**
                 * @brief Destroy the Component Map object
                 *
                 */
                ~ComponentMap() = default;

                /**
                 * @brief delete all the components in the map from the given entity
                 *
                 * @param entity the entity id from which the components will be deleted
                 */
                void deleteEntityComponents(entity_t entity)
                {
                    if (_data.count(entity) == 0)
                        return;
                    _data.erase(entity);
                }

                /**
                 * @brief add a new component in the map with the given entity id as a key
                 *
                 * @param component the new component to add
                 * @param entity the id of the entity
                 */
                void put(Component &component, entity_t entity)
                {
                    if (typeid(Component) == typeid(Network))
                        std::cout << "put to nework" << std::endl;
                    _data[entity] = component;
                    if (typeid(Component) == typeid(Network))
                        std::cout << "end of put to nework" << std::endl;
                }

                /**
                 * @brief remove and return the component from the given entity id
                 *
                 * @param entity the id of the entity
                 * @return the component that has been removed as a Component&
                 */
                Component &pop(entity_t entity)
                {
                    Component &value = _data[entity];

                    _data.erase(entity);
                    return value;
                }

                /**
                 * @brief check if the map contains a component with the given entity id as his key
                 *
                 * @param entity the id of the entity
                 * @return true if the map a component with the given entity id, false otherwise
                 */
                bool contains(entity_t entity)
                {
                    if (_data.empty())
                            return false;
                    return _data.count(entity) == 1;
                }

                /**
                 * @brief check if the map contains an entity with the given component
                 *
                 * @param component the component to check the entity existence with
                 * @return true if the entity exists in the map, false otherwise
                 */
                bool contains(Component &component)
                {
                    for (auto &values : _data) {
                        if (component == values.second)
                            return true;
                    }
                    return false;
                }

                /**
                 * @brief Get the component from the map index
                 *
                 * @param index the index in the map
                 * @return the component in the index position in the map as a Component&
                 */
                Component &getFromIndex(uint32_t index)
                {
                    uint32_t it = 0;

                    for (auto &values : _data) {
                        if (it == index)
                            return values.second;
                        it++;
                    }
                    throw std::invalid_argument("Invalid index in getFromIndex");
                }

                /**
                 * @brief Get the entity's component in the map
                 *
                 * @param entity the entity id for the component
                 * @return the component as a Component&
                 */
                Component &get(entity_t entity)
                {
                    if (_data.count(entity) == 0)
                        throw std::invalid_argument("entity doesn't exist in componentMap !");
                    return _data[entity];
                }

                /**
                 * @brief Get the component's entity id in the map
                 *
                 * @param component the component for the entity
                 * @return the entity id as a const entity_t&
                 */
                const entity_t &getEntityId(const Component &component) const
                {
                    for (auto &values : _data) {
                        if (component == values.second)
                            return values.first;
                    }
                    throw std::invalid_argument("Invalid index in getEntityId");
                }

                /**
                 * @brief Get the number of elements in the map
                 *
                 * @return the number of elements as a uint32_t
                 */
                uint32_t getSize() const
                {
                    return _data.size();
                }

                /**
                 * @brief add another map's data in the map
                 *
                 * @param other the other map to add
                 * @return the current ComponentMap object as a ComponentMap<Component>&
                 */
                ComponentMap<Component> &operator+=(ComponentMap<Component> const &other)
                {
                    for (auto value : other._data) {
                        if (_data.count(value.first) == 0)
                            _data[value.first] = value.second;
                    }
                    return *this;
                }

            protected:
                /**
                 * @brief the data to store the components as values and entity id as keys
                 *
                 */
                std::unordered_map<entity_t, Component> _data;
        };
    }

#endif /* !ComponentMapDef */