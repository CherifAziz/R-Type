/*
** EPITECH PROJECT, 2023
** SfmlInputSystem
** File description:
** SfmlInputSystem
*/

#ifndef _SfmlInputSystem_
    #define _SfmlInputSystem_

    #include <SFML/Graphics.hpp>

    #include <memory>

    #include "AInputSystem.hpp"
    #include "IScene.hpp"

    #include "Entity.hpp"
    #include "Action.hpp"

    #include "Storage.hpp"

    namespace rtype {
        /**
         * @brief The Input System for SFML library
         * 
         */
        class SfmlInputSystem : public AInputSystem {
            public:
                /**
                 * @brief Construct a new Sfml Input System object with the "SFML" library name
                 * 
                 */
                SfmlInputSystem();

                /**
                 * @brief Destroy the Sfml Input System object
                 * 
                 */
                ~SfmlInputSystem();

                /**
                 * @brief init the Sfml Input System object
                 * 
                 * @details get the singleton storage
                 */
                void init();

                /**
                 * @brief update the input sytem
                 * 
                 * @param scene the current game scene
                 */
                void update(std::shared_ptr<IScene> &scene);

                /**
                 * @brief Destroy the Sfml Input System properties
                 * 
                 */
                void destroy();

                /**
                 * @brief check if the game is still playing
                 * 
                 * @return true if the game is still playing, false otherwise
                 */
                bool isGameStillPlaying();

                /**
                 * @brief Get the Current Scene object
                 * 
                 * @return the current scene as a const size_t&
                 */
                const size_t &getCurrentScene() const;

            private:
                /**
                 * @brief update the system by checking if new event were triggered
                 * 
                 * @param action the Action ComponentMap
                 * @param entity the player entity id
                 * 
                 * @return true if the window has been closed, false otherwise
                 */
                bool checkEvent(std::shared_ptr<ComponentMap<Action>> action, entity_t entity);

                /**
                 * @brief handle the event by setting the key state in the Action component
                 * 
                 * @param event the key state (pressed or released)
                 * @param key the key type (keyboard key)
                 * @param action the player's Action component
                 */
                void handleKey(sf::Event::EventType event, sf::Keyboard::Key key, Action &action);

                /**
                 * @brief the singleton storage
                 * 
                 */
                std::shared_ptr<Storage> _storage;

                /**
                 * @brief the window's event polled
                 * 
                 */
                sf::Event _event;

                /**
                 * @brief the key translation between the SFML library and Action Component KeyType enum
                 * 
                 */
                const std::unordered_map<sf::Keyboard::Key, Action::KeyType> _keyTranslator = {
                    {sf::Keyboard::Z, Action::KeyType::Z},
                    {sf::Keyboard::S, Action::KeyType::S},
                    {sf::Keyboard::Q, Action::KeyType::Q},
                    {sf::Keyboard::D, Action::KeyType::D},
                    {sf::Keyboard::Space, Action::KeyType::SPACE}
                };
        };
    }

#endif /* !_SfmlInputSystem_ */