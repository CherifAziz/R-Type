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
                 * @brief Every Mouse key used by the game
                 * 
                 */
                enum class MouseType {
                    Left
                };

                /**
                 * @brief Mouse Positions
                 * 
                 */
                struct MousePosition {
                    float X;
                    float Y;
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
                Action();

                /**
                 * @brief Destroy the Action object
                 * 
                 */
                ~Action();

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

                /**
                 * @brief Set the State object
                 * 
                 * @param mouseKey the mouse key that will be set in the key map as a key
                 * @param state the mouse key state that will be set in the key map as the value
                 */
                void setMouseState(const MouseType &mouseKey, const KeyState &state)
                {
                    _mouseKeys[mouseKey] = state;
                }

                /**
                 * @brief Get the Key State object
                 * 
                 * @param mouseKey the key to get the state from
                 * @return the state as a const KeyState& 
                 */
                const KeyState &getMouseKeyState(const MouseType &mouseKey) const { return _mouseKeys.at(mouseKey); }

                /**
                 * @brief Set the Mouse position
                 * 
                 * @param X mouse position at coordinate X
                 * @param Y mouse position at coordinate Y
                 */
                void setMousePosition(const float &X, const float &Y)
                {
                    _mousePosition.X = X;
                    _mousePosition.Y = Y;
                }

                /**
                 * @brief Get the Mouse Position
                 * 
                 * @return the mouse position at &MousePosition 
                 */
                const MousePosition &getMousePosition() const { return _mousePosition; }

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

                /**
                 * @brief the key map with the mouse key as a key and the key state as the value
                 * 
                 */
                std::unordered_map<MouseType, KeyState> _mouseKeys = {
                    {MouseType::Left, KeyState::UP}
                };

                struct MousePosition _mousePosition;
        };
    }

#endif /* !ActionDef */
