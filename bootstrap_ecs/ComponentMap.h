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

    template <typename Component>
    class ComponentMap
    {
        public:
            ComponentMap(){};
            ~ComponentMap(){};
            void put(Component &component) {
                _data.push_back(component);
            }
            Component &pop(const size_t index) {
                Component &value = _data.at(index);

                _data.erase(std::find(_data.begin(), _data.end(), _data.at(index)));
                return value;
            }
            Component &get(const size_t index) {
                return _data.at(index);
            }
            size_t get_index(Component &component) const {
                auto it = std::find(_data.begin(), _data.end(), component);

                if (it != _data.end())
                    return (it - _data.begin());
                return (-1);
            }
            void display() {
                std::cout << "size: " << _data.size() << std::endl;
                for (int it = 0; it < _data.size(); it++)
                    std::cout << it << std::endl;
                std::cout << std::endl;
            }
            
            ComponentMap<Component> &operator+=(ComponentMap<Component> const &other)
            {
                for (auto value : other._data) {
                    _data.push_back(value);
                }
                return *this;
            }

            ComponentMap<Component> &operator=(ComponentMap<Component> const &other)
            {
                _data = other._data;
                return *this;
            }
        private:
            std::vector<Component> _data;
    };

#endif /* !ComponentMap */