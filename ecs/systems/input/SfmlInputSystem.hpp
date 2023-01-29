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

    #include "Entity.hpp"
    #include "Action.hpp"

    class SfmlInputSystem : public AInputSystem {
        public:
            SfmlInputSystem() : AInputSystem("Sfml") {}
            ~SfmlInputSystem() = default;

            void update(sf::RenderWindow &window, std::shared_ptr<ComponentMap<Action>> action, entity_t entity)
            {
                while (window.pollEvent(_event)) {
                    if (_event.type == sf::Event::Closed)
                        window.close();
                    else if (_event.type == sf::Event::KeyPressed || _event.type == sf::Event::KeyReleased)
                        handleKey(_event.type, _event.key.code, action->get(entity));
                }
            }

        private:
            void handleKey(sf::Event::EventType event, sf::Keyboard::Key key, Action &action)
            {
                if (_keyTranslator.count(key) == 0)
                    return;

                if (event == sf::Event::KeyPressed)
                    action.setState(_keyTranslator.at(key), Action::KeyState::PRESSED);
                else if (event == sf::Event::KeyReleased)
                    action.setState(_keyTranslator.at(key), Action::KeyState::RELEASED);
            }

            sf::Event _event;

            const std::unordered_map<sf::Keyboard::Key, Action::KeyType> _keyTranslator = {
                {sf::Keyboard::Z, Action::KeyType::Z},
                {sf::Keyboard::S, Action::KeyType::S},
                {sf::Keyboard::Q, Action::KeyType::Q},
                {sf::Keyboard::D, Action::KeyType::D},
                {sf::Keyboard::Space, Action::KeyType::SPACE}
            };
    };

#endif /* !_SfmlInputSystem_ */