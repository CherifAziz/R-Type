/*
** EPITECH PROJECT, 2023
** Collision
** File description:
** Collision
*/

#ifndef _Collision_
    #define _Collision_

    #include <string>
    #include <vector>
    #include <algorithm>

    namespace rtype {
        /**
         * @brief the Collision Component
         * 
         */
        class Collision {
            public:
                /**
                 * @brief Construct a new Collision object
                 * 
                 * @param families the families that will enter in collision with the entity
                 */
                Collision(const std::vector<std::string> &families = {}) : _families(families) {}

                /**
                 * @brief Destroy the Collision object
                 * 
                 */
                ~Collision() = default;

                /**
                 * @brief Get all the Families object
                 * 
                 * @return the families as a const std::vector<std::string>& 
                 */
                const std::vector<std::string> &getFamilies() const { return _families; }

                /**
                 * @brief Set the Families object
                 * 
                 * @param families the families that will be assign that will enter in collision with the entities
                 */
                void setFamilies(const std::vector<std::string> &families) { _families = families; }

                /**
                 * @brief check if the entity will collide with the given family
                 * 
                 * @param family the given family to check with
                 * @return true if the entity collide, false otherwise
                 */
                bool isColliding(const std::string &family) { return std::find(_families.begin(), _families.end(), family) != _families.end(); }

                /**
                 * @brief check if the collisions components are the same
                 * 
                 * @param other the collision component that will be compared
                 * @return true if the component are the same, false otherwise
                 */
                bool operator==(const Collision &other) const { return _families == other._families; }
            protected:
                /**
                 * @brief the families that can enter in collision with the entity
                 * 
                 */
                std::vector<std::string> _families;
        };
    }

#endif /* !_Collision_ */