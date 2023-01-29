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

    #include "Movement.hpp"

    class SfmlInputSystem : public AInputSystem {
        public:
            SfmlInputSystem() : AInputSystem("Sfml") {}
            ~SfmlInputSystem() = default;

            void update(sf::RenderWindow &window, std::shared_ptr<ComponentMap<Movement>> movement)
            {
                while (window.pollEvent(_event)) {
                    if (_event.type == sf::Event::Closed)
                        window.close();
                    else if (_event.type == sf::Event::KeyPressed || _event.type == sf::Event::KeyReleased)
                        handleKey(_event.type, _event.key.code, movement->getFromIndex(0));
                }
            }

        private:
            void handleKey(sf::Event::EventType event, sf::Keyboard::Key key, Movement &movement)
            {
                if (_keyTranslator.count(key) == 0)
                    return;

                if (event == sf::Event::KeyPressed)
                    movement.setState(_keyTranslator.at(key), Movement::KeyState::PRESSED);
                else if (event == sf::Event::KeyReleased)
                    movement.setState(_keyTranslator.at(key), Movement::KeyState::RELEASED);
            }

            sf::Event _event;

            const std::unordered_map<sf::Keyboard::Key, Movement::KeyType> _keyTranslator = {
                {sf::Keyboard::Z, Movement::KeyType::Z},
                {sf::Keyboard::S, Movement::KeyType::S},
                {sf::Keyboard::Q, Movement::KeyType::Q},
                {sf::Keyboard::D, Movement::KeyType::D}
            };
    };

#endif /* !_SfmlInputSystem_ */