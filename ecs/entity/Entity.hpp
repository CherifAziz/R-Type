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
            ~Entity() = default;

            const unsigned long &getId() const { return _id; }
            void setId(const int &id) { _id = id; }
            const std::string &getFamily() const { return _family; }
            void setFamily(const std::string &family) { _family = family; }
            const EntityStatus &getStatus() const { return _status; }
            void setStatus(const EntityStatus &status) { _status = status; }

            const bool &isShown() const { return _isShown; }
            void hide() { _isShown = false; }
            void show() { _isShown = true; }

        protected:
            unsigned long _id;
            std::string _family;
            EntityStatus _status = EntityStatus::ALIVE;
            bool _isShown = true;
    };

#endif /* !_Entity_ */