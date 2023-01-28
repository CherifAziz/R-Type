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

            void deleteEntityComponents(unsigned long entity)
            {
                if (_data.count(entity) == 0)
                    return;
                _data.erase(entity);
            }

            void put(Component &component, unsigned long entity)
            {
                _data[entity] = component;
            }

            Component &pop(unsigned long entity)
            {
                Component &value = _data[entity];

                _data.erase(entity);
                return value;
            }

            bool contains(unsigned long entity)
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

            Component &get_from_index(uint32_t index)
            {
                uint32_t it = 0;

                for (auto &values : _data) {
                    if (it == index)
                        return values.second;
                    it++;
                }
                throw std::runtime_error("Invalid index in get_from_index");
            }

            Component &get(unsigned long entity)
            {
                return _data[entity];
            }

            unsigned long getEntityId(Component &component) const
            {
                for (auto &values : _data) {
                    if (component == values.second)
                        return values.first;
                }
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

        private:
            std::unordered_map<unsigned long, Component> _data;
    };

#endif /* !ComponentMap */