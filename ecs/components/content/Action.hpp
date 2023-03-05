/*
** EPITECH PROJECT, 2023
** Action
** File description:
** Action
*/

#ifndef ActionDef
    #define ActionDef

    #include <unordered_map>

    namespace rtype {
        /**
         * @brief the Action Component
         * 
         */
        class Action {
            public:
                /**
                 * @brief Every keyboard key used by the game
                 * 
                 */
                enum class KeyType {
                    Z,
                    S,
                    Q,
                    D,
                    SPACE
                };

                /**
                 * @brief The state of a key (UP, PRESSED, DOWN or RELEASED)
                 * 
                 */
                enum class KeyState {
                    PRESSED,
                    DOWN,
                    RELEASED,
                    UP
                };

                /**
                 * @brief Construct a new Action object
                 * 
                 */
                Action() = default;

                /**
                 * @brief Destroy the Action object
                 * 
                 */
                ~Action() = default;

                /**
                 * @brief Set the State object
                 * 
                 * @param key the keyboard key that will be set in the key map as a key
                 * @param state the keyboard key state that will be set in the key map as the value
                 */
                void setState(const KeyType &key, const KeyState &state);

                /**
                 * @brief Get the Key State object
                 * 
                 * @param key the key to get the state from
                 * @return the state as a const KeyState& 
                 */
                const KeyState &getKeyState(const KeyType &key) const { return _keys.at(key); }

            protected:
                /**
                 * @brief the key map with the keyboard key as a key and the key state as the value
                 * 
                 */
                std::unordered_map<KeyType, KeyState> _keys = {
                    {KeyType::Z, KeyState::UP},
                    {KeyType::S, KeyState::UP},
                    {KeyType::Q, KeyState::UP},
                    {KeyType::D, KeyState::UP},
                    {KeyType::SPACE, KeyState::UP}
                };
        };
    }

#endif /* !ActionDef */
