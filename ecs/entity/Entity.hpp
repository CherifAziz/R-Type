/*
** EPITECH PROJECT, 2023
** Entity
** File description:
** Entity
*/

#ifndef _Entity_
    #define _Entity_

    #include <string>

    class Entity {
        public:
            enum class EntityStatus {
                ALIVE,
                DEAD,
                USED
            };

            Entity(const unsigned long &id = 0, const std::string &family = "") : _id(id), _family(family) {}
            ~Entity();

            const int &get_id() const { return _id; }
            void set_id(const int &id) { _id = id; }
            const std::string &get_family() const { return _family; }
            void set_family(const std::string &family) { _family = family; }
            const EntityStatus &get_status() const { return _status; }
            void set_status(const EntityStatus &status) { _status = status; }

        private:
            unsigned long _id;
            std::string _family;
            EntityStatus _status = EntityStatus::ALIVE;
    };

#endif /* !_Entity_ */