/*
** EPITECH PROJECT, 2023
** test
** File description:
** 02
*/

#include <iostream>
#include <typeindex>
#include <unordered_map>
#include <map>
#include <memory>
#include <string>

#include "ComponentMap.h"

class A {
    public:
        A(int value) : _value(value) {};
        void display() {
            std::cout << _value << std::endl;
        }
    private:
        int _value;
};

class B {
    public:
        B(char value) : _value(value) {};
        void display() {
            std::cout << _value << std::endl;
        }
    private:
        char _value;
};

class C {
    public:
        C(std::string value) : _value(value) {};
        void display() {
            std::cout << _value << std::endl;
        }
    private:
        std::string _value;
};

class ComponentManager {
    public:
        entity_t spawn_entity()
        {
            entity_t new_entity = -1;

            for (auto &entity : _entity_status) {
                if (entity.second == EntityStatus::DEAD) {
                    new_entity = entity.first;
                    entity.second = EntityStatus::USED;
                    break;
                }
            }
            if (new_entity == -1)
                new_entity = (--_entity_status.end())->first + 1;
            _entity_status[new_entity] = EntityStatus::ALIVE;
            return new_entity;
        }

        void kill_entity(const entity_t &entity)
        {
            for (auto &components : _components)
                components.second->delete_entity_components(entity);
            _entity_status[entity] = EntityStatus::DEAD;
        }

        template <class Component>
        void register_component(ComponentMap<Component> new_component)
        {
            if (_components.count(std::type_index(typeid(Component))) == 0) {
                _components[std::type_index(typeid(Component))] = std::make_shared<ComponentMap<Component>>(new_component);
            } else {
                std::cerr << "component map has already been registered" << std::endl;
            }
        }

        template <class Component>
        ComponentMap<Component> &get_components()
        {
            return (std::static_pointer_cast<ComponentMap<Component>&>(_components[std::type_index(typeid(Component))]));
        }

        template <class Component>
        void remove_components(const entity_t &entity)
        {
            _components[std::type_index(typeid(Component))]->delete_entity_components(entity);
        }

    private:
        enum class EntityStatus {
            ALIVE,
            DEAD,
            USED
        };

        std::map<entity_t, EntityStatus> _entity_status;
        std::unordered_map<std::type_index, std::shared_ptr<IComponentMap>> _components;
};

int main(void)
{
    ComponentManager manager;
    A a(42);
    A a2(21);
    A a3(7);
    B b('z');
    B b2('r');
    B b3('j');
    C c("Arthur");
    C c2("Thomas");
    C c3("Jules");

    ComponentMap<A> a_map;
    a_map.put(a);
    a_map.put(a2);
    a_map.put(a3);
    ComponentMap<B> b_map;
    b_map.put(b);
    b_map.put(b2);
    b_map.put(b3);
    ComponentMap<C> c_map;
    c_map.put(c);
    c_map.put(c2);
    c_map.put(c3);
    manager.register_component<A>(a_map);
    manager.register_component<B>(b_map);
    manager.register_component<C>(c_map);

    b_map.display();
    ComponentMap<B> test = manager.get_components<B>();
    test.display();
    B bbbb = test.get(0);
    bbbb.display();


    return (0);
}