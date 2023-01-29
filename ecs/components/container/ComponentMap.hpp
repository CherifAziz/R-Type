/*
** EPITECH PROJECT, 2023
** ComponentMap
** File description:
** ComponentMap
*/

#ifndef ComponentMap
    #define ComponentMapClass

    #include <unordered_map>
    #include <algorithm>
    #include <iostream>

    #include "Entity.hpp"

    #include "IComponentMap.hpp"

    template <typename Component>
    class ComponentMap : public IComponentMap
    {
        public:
            ComponentMap()
            {
            }

            ~ComponentMap()
            {
            }

            void deleteEntityComponents(entity_t entity)
            {
                if (_data.count(entity) == 0)
                    return;
                _data.erase(entity);
            }

            void put(Component component, entity_t entity)
            {
                _data[entity] = component;
            }

            Component &pop(entity_t entity)
            {
                Component &value = _data[entity];

                _data.erase(entity);
                return value;
            }

            bool contains(entity_t entity)
            {
                if (_data.empty())
                    return false;
                return _data.count(entity) == 1;
            }

            bool contains(Component &component)
            {
                for (auto &values : _data) {
                    if (component == values.second)
                        return true;
                }
                return false;
            }

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

            Component &get(entity_t entity)
            {
                return _data[entity];
            }

            const entity_t &getEntityId(const Component &component) const
            {
                for (auto &values : _data) {
                    if (component == values.second)
                        return values.first;
                }
                throw std::invalid_argument("Invalid index in getEntityId");
            }

            uint32_t getSize() const
            {
                return _data.size();
            }

            ComponentMap<Component> &operator+=(ComponentMap<Component> const &other)
            {
                for (auto value : other._data) {
                    if (_data.count(value.first) == 0)
                        _data[value.first] = value.second;
                }
                return *this;
            }

        protected:
            std::unordered_map<entity_t, Component> _data;
    };

#endif /* !ComponentMap */