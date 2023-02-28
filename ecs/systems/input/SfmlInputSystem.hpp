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
    #include <string>
    #include <iostream>

    #include "AInputSystem.hpp"
    #include "IScene.hpp"

    #include "Entity.hpp"
    #include "Action.hpp"
    #include "Network.hpp"

    #include "Storage.hpp"
    #include "Serialize.hpp"
    #include "Services.hpp"

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
                SfmlInputSystem() : AInputSystem("Sfml") {}

                /**
                 * @brief Destroy the Sfml Input System object
                 *
                 */
                ~SfmlInputSystem() = default;

                /**
                 * @brief init the Sfml Input System object
                 *
                 * @details get the singleton storage
                 */
                void init()
                {
                    _storage = Storage::getStorage();
                }

                /**
                 * @brief update the input sytem
                 *
                 * @param scene the current game scene
                 */
                void update(std::shared_ptr<IScene> &scene)
                {
                    std::shared_ptr<ComponentMap<Network>> networkMap = scene->getComponentManager().getComponents<Network>();
                    std::shared_ptr<ComponentMap<Action>> actionMap = scene->getComponentManager().getComponents<Action>();
                    std::vector<std::shared_ptr<Entity>> players = scene->getEntityManager().getEntitiesFromFamily("player");

                    for (const auto &player : players) {
                        if (checkEvent(actionMap, networkMap, player->getId()) == true) {
                            _storage->getRenderWindow().close();
                            return;
                        }
                    }
                }

                /**
                 * @brief Destroy the Sfml Input System properties
                 *
                 */
                void destroy()
                {

                }

                /**
                 * @brief check if the game is still playing
                 *
                 * @return true if the game is still playing, false otherwise
                 */
                bool isGameStillPlaying()
                {
                    return _storage->getRenderWindow().isOpen();
                }

                /**
                 * @brief Get the Current Scene object
                 *
                 * @return the current scene as a const size_t&
                 */
                const size_t &getCurrentScene() const
                {
                    return _storage->getCurrentScene();
                }

            private:
                /**
                 * @brief update the system by checking if new event were triggered
                 *
                 * @param action the Action ComponentMap
                 * @param entity the player entity id
                 *
                 * @return true if the window has been closed, false otherwise
                 */
                bool checkEvent(std::shared_ptr<ComponentMap<Action>> action, std::shared_ptr<ComponentMap<Network>> network, entity_t entity)
                {
                    while (_storage->getRenderWindow().pollEvent(_event)) {
                        if (_event.type == sf::Event::Closed) {
                            _storage->getRenderWindow().close();
                            return true;
                        }
                        else if (_event.type == sf::Event::KeyPressed || _event.type == sf::Event::KeyReleased) {
                            try {
                                handleKey(_event.type, _event.key.code, action->get(entity), network->get(entity));
                            } catch (...) {
                                handleKey(_event.type, _event.key.code, action->get(entity));
                            }
                        }
                    }
                    return false;
                }

                /**
                 * @brief handle the event by setting the key state in the Action component
                 *
                 * @param event the key state (pressed or released)
                 * @param key the key type (keyboard key)
                 * @param action the player's Action component
                 */
                void handleKey(sf::Event::EventType event, sf::Keyboard::Key key, Action &action)
                {
                    if (_keyTranslator.count(key) == 0)
                        return;

                    if (event == sf::Event::KeyPressed) {
                        action.setState(_keyTranslator.at(key), Action::KeyState::PRESSED);
                    } else if (event == sf::Event::KeyReleased) {
                        action.setState(_keyTranslator.at(key), Action::KeyState::RELEASED);
                    }
                }

                void handleKey(sf::Event::EventType event, sf::Keyboard::Key key, Action &action, Network &network)
                {
                    if (_keyTranslator.count(key) == 0)
                        return;

                    if (event == sf::Event::KeyPressed) {
                        action.setState(_keyTranslator.at(key), Action::KeyState::PRESSED);
                        network.addToQueue(Serialize::createData<Serialize::Data>(Services::Command::INPUT, {boost::uuids::to_string(network.getUUID()), std::to_string(_keyTranslator.at(key)), std::to_string(Action::KeyState::PRESSED) }));
                    } else if (event == sf::Event::KeyReleased) {
                        action.setState(_keyTranslator.at(key), Action::KeyState::RELEASED);
                        network.addToQueue(Serialize::createData<Serialize::Data>(Services::Command::INPUT, {boost::uuids::to_string(network.getUUID()), std::to_string(_keyTranslator.at(key)), std::to_string(Action::KeyState::RELEASED) }));
                    }
                }

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