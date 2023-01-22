/*
** EPITECH PROJECT, 2023
** ComponentMap
** File description:
** ComponentMap
*/

#ifndef ComponentMap
    #define ComponentMapClass

    #include <vector>
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
                auto it = std::find_if(_data.begin(), _data.end(),
                [&entity](const std::pair<Component, entity_t> &value)
                { return value.second == entity; });

                while (it != _data.end()) {
                    _data.erase(it);
                    it = std::find_if(_data.begin(), _data.end(),
                    [&entity](const std::pair<Component, entity_t> &value)
                    { return value.second == entity; });
                }
            }

            void put(Component &component, entity_t entity)
            {
                _data.push_back(std::make_pair(component, entity));
            }

            Component &pop(const size_t index)
            {
                Component &value = _data.at(index).first;

                _data.erase(std::find(_data.begin(), _data.end(), _data.at(index)));
                return value;
            }

            const Component &get(const size_t index)
            {
                return _data.at(index).first;
            }

            const std::vector<Component> &get_from_entity(const entity_t &entity)
            {
                std::vector<Component> components;

                for (auto &component : _data) {
                    if (component.second == entity)
                        components.push_back(component);
                }
                return components;
            }

            size_t get_index(Component &component) const
            {
                auto it = std::find_if(_data.begin(), _data.end(),
                [&component](const std::pair<Component, entity_t> &value)
                { return value.first == component; });

                if (it != _data.end())
                    return (it - _data.begin());
                return (-1);
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
                    _data.push_back(std::make_pair(value.first, value.second));
                }
                return *this;
            }

            ComponentMap<Component> &operator=(ComponentMap<Component> const &other)
            {
                _data = other._data;
                return *this;
            }

        private:
            std::vector<std::pair<Component, entity_t>> _data;
    };

#endif /* !ComponentMap */