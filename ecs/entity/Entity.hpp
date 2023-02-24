/*
** EPITECH PROJECT, 2023
** Entity
** File description:
** Entity
*/

#ifndef _Entity_
    #define _Entity_

    #include <string>

    #define entity_t    unsigned long

    namespace rtype {
        /**
         * @brief the class for an entity
         * 
         */
        class Entity {
            public:
                /**
                 * @brief this enum is used to know the entity id state
                 * 
                 * @details if the entity is ALIVE, the id is used, if it's DEAD it's not used by the game anymore but is id can be recycled for a new entity.
                 * Finally if the entity is USED, this entity is dead and is id has been recycled
                 */
                enum class EntityStatus {
                    ALIVE,
                    DEAD,
                    USED
                };

                /**
                 * @brief Construct a new Entity object but you don't need to call this method, the EntityManager already call it is the spawn entity method
                 * 
                 * @param id the entity id 
                 * @param family 
                 */
                Entity(const unsigned long &id = 0, const std::string &family = "") : _id(id), _family(family) {}

                /**
                 * @brief Destroy the Entity object
                 * 
                 */
                ~Entity() = default;

                /**
                 * @brief Get the Id object
                 * 
                 * @return the id as a const unsigned long& 
                 */
                const unsigned long &getId() const { return _id; }

                /**
                 * @brief Set the Id object
                 * 
                 * @param id the id that will be assigned
                 */
                void setId(const int &id) { _id = id; }

                /**
                 * @brief Get the Family object
                 * 
                 * @return the family as a const std::string& 
                 */
                const std::string &getFamily() const { return _family; }

                /**
                 * @brief Set the Family object
                 * 
                 * @param family the family that will be assigned
                 */
                void setFamily(const std::string &family) { _family = family; }

                /**
                 * @brief Get the Status object
                 * 
                 * @return the status as a const EntityStatus& 
                 */
                const EntityStatus &getStatus() const { return _status; }

                /**
                 * @brief Set the Status object
                 * 
                 * @param status the status that will be assigned
                 */
                void setStatus(const EntityStatus &status) { _status = status; }

                /**
                 * @brief check if the entity is shown in the game
                 * 
                 * @return true if the entity is shown, false otherwise
                 */
                const bool &isShown() const { return _isShown; }

                /**
                 * @brief hide the entity
                 * 
                 */
                void hide() { _isShown = false; }

                /**
                 * @brief display the entity
                 * 
                 */
                void show() { _isShown = true; }

            protected:
                /**
                 * @brief the entity's id
                 * 
                 */
                entity_t _id;

                /**
                 * @brief the entity's family
                 * 
                 */
                std::string _family;

                /**
                 * @brief the entity current status, ALIVE by default
                 * 
                 */
                EntityStatus _status = EntityStatus::ALIVE;

                /**
                 * @brief the entity shown boolean value, true by default
                 * 
                 */
                bool _isShown = true;
        };
    }

#endif /* !_Entity_ */