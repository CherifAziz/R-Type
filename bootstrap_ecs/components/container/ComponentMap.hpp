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

            void delete_entity_components(const entity_t &entity)
            {
                if (_data.count(entity) == 0)
                    return;
                _data.erase(entity);
            }

            void put(Component &component, const entity_t &entity)
            {
                _data[entity] = component;
            }

            Component &pop(const entity_t &entity)
            {
                Component &value = _data[entity];

                _data.erase(entity);
                return value;
            }

            Component &get(const entity_t &entity)
            {
                return _data[entity];
            }

            const entity_t &get_entity_id(Component &component) const
            {
                for (auto &values : _data) {
                    if (component == values.second)
                        return values.first;
                }
            }

            size_t get_size() const
            {
                return _data.size();
            }

            void display()
            {
                std::cout << "size: " << _data.size() << std::endl;
                for (int it = 0; it < _data.size(); it++)
                    std::cout << it << std::endl;
                std::cout << std::endl;
            }

            ComponentMap<Component> &operator+=(ComponentMap<Component> const &other)
            {
                for (auto value : other._data) {
                    if (_data.count(value.first) == 0)
                        _data[value.first] = value.second;
                }
                return *this;
            }

            ComponentMap<Component> &operator=(ComponentMap<Component> const &other)
            {
                _data = other._data;
                return *this;
            }

        private:
            std::unordered_map<entity_t, Component> _data;
    };

#endif /* !ComponentMap */