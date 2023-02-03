/*
** EPITECH PROJECT, 2023
** Action
** File description:
** Action
*/

#ifndef _Action_
    #define _Action_

    #include <unordered_map>

    namespace rtype {
        class Action {
            public:
                enum class KeyType {
                    Z,
                    S,
                    Q,
                    D,
                    SPACE
                };

                enum class KeyState {
                    UP,
                    PRESSED,
                    DOWN,
                    RELEASED
                };

                void setState(const KeyType &key, const KeyState &state)
                {
                    _keys[key] = state;
                }

                const KeyState &getKeyState(const KeyType &key) const { return _keys.at(key); }

                Action() = default;
                ~Action() = default;

            protected:
                std::unordered_map<KeyType, KeyState> _keys = {
                    {KeyType::Z, KeyState::UP},
                    {KeyType::S, KeyState::UP},
                    {KeyType::Q, KeyState::UP},
                    {KeyType::D, KeyState::UP},
                    {KeyType::SPACE, KeyState::UP}
                };
        };
    }

#endif /* !_Action_ */
