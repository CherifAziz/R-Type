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
                _data[entity] = std::make_pair(component, true);
            }

            Component &pop(unsigned long entity)
            {
                Component &value = _data[entity].first;

                _data.erase(entity);
                return value;
            }

            bool contains(unsigned long entity)
            {
                return _data.count(entity) == 1;
            }

            bool contains(Component &component)
            {
                for (auto &values : _data) {
                    if (component == values.second.first)
                        return true;
                }
                return false;
            }

            const bool &isComponentActive(unsigned long entity)
            {
                return _data[entity].second;
            }

            void setComponentState(unsigned long entity, bool isActive)
            {
                _data[entity].second = isActive;
            }

            Component &get(unsigned long entity)
            {
                return _data[entity].first;
            }

            unsigned long getEntityId(Component &component) const
            {
                for (auto &values : _data) {
                    if (component == values.second.first)
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
            std::unordered_map<unsigned long, std::pair<Component, bool>> _data;
    };

#endif /* !ComponentMap */