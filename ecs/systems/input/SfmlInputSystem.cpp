/*
** EPITECH PROJECT, 2023
** SfmlInputSystem
** File description:
** SfmlInputSystem
*/

#include "SfmlInputSystem.hpp"

namespace rtype {

    SfmlInputSystem::SfmlInputSystem() : AInputSystem("Sfml")
    {
    }

    SfmlInputSystem::~SfmlInputSystem()
    {
    }

    void SfmlInputSystem::init()
    {
        _storage = Storage::getStorage();
    }

    void SfmlInputSystem::update(std::shared_ptr<IScene> &scene)
    {
        std::shared_ptr<ComponentMap<Action>> actionMap = scene->getComponentManager().getComponents<Action>();
        std::vector<std::shared_ptr<Entity>> players = scene->getEntityManager().getEntitiesFromFamily("player");

        for (const auto &player : players) {
            if (checkEvent(actionMap, player->getId()) == true) {
                _storage->getRenderWindow().close();
                return;
            }
        }
    }
    bool SfmlInputSystem::isGameStillPlaying()
    {
        return _storage->getRenderWindow().isOpen();
    }

    const size_t &SfmlInputSystem::getCurrentScene() const
    {
        return _storage->getCurrentScene();
    }

    bool SfmlInputSystem::checkEvent(std::shared_ptr<ComponentMap<Action>> action, entity_t entity)
    {
        while (_storage->getRenderWindow().pollEvent(_event)) {
            if (_event.type == sf::Event::Closed) {
                _storage->getRenderWindow().close();
                return true;
            }
            else if (_event.type == sf::Event::KeyPressed || _event.type == sf::Event::KeyReleased)
                handleKey(_event.type, _event.key.code, action->get(entity));
        }
        return false;
    }

    void SfmlInputSystem::handleKey(sf::Event::EventType event, sf::Keyboard::Key key, Action &action)
    {
        if (_keyTranslator.count(key) == 0)
            return;

        if (event == sf::Event::KeyPressed)
            action.setState(_keyTranslator.at(key), Action::KeyState::PRESSED);
        else if (event == sf::Event::KeyReleased)
            action.setState(_keyTranslator.at(key), Action::KeyState::RELEASED);
    }
}