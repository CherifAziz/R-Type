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

    class Collision {
        public:
            Collision(const std::vector<std::string> &families = {}) : _families(families) {}
            ~Collision() = default;

            const std::vector<std::string> &getFamilies() const { return _families; }
            void setFamilies(const std::vector<std::string> &families) { _families = families; }
            bool isColliding(const std::string &family) { return std::find(_families.begin(), _families.end(), family) != _families.end(); }
        private:
            std::vector<std::string> _families;
    };

#endif /* !_Collision_ */