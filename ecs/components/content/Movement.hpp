/*
** EPITECH PROJECT, 2023
** Movement
** File description:
** Movement
*/

#ifndef _Movement_
    #define _Movement_

    #include <unordered_map>

    class Movement {
        public:
            enum class KeyType {
                Z,
                S,
                Q,
                D
            };

            enum class KeyState {
                UP,
                PRESSED,
                DOWN,
                RELEASED
            };

            Movement(const int &xDirection = 0, const int &yDirection = 0) : _xDirection(xDirection), _yDirection(yDirection) {};
            ~Movement() = default;

            const int &getXDirection() const { return _xDirection; };
            const int &getYDirection() const { return _yDirection; };
            void setDirection(const int &xDirection, const int &yDirection)
            {
                _xDirection = xDirection;
                _yDirection = yDirection;
            }

            void setState(const KeyType &key, const KeyState &state)
            {
                _keys[key] = state;
            }

            const KeyState &getKeyState(const KeyType &key) const { return _keys.at(key); }

            bool operator==(const Movement &other) const
            {
                return _xDirection == other._xDirection && _yDirection == other._yDirection;
            }

        protected:
            int _xDirection;
            int _yDirection;
            std::unordered_map<KeyType, KeyState> _keys = {
                {KeyType::Z, KeyState::UP},
                {KeyType::S, KeyState::UP},
                {KeyType::Q, KeyState::UP},
                {KeyType::D, KeyState::UP}
            };
    };

#endif /* !_Movement_ */
