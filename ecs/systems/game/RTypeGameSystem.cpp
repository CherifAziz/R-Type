/*
** EPITECH PROJECT, 2023
** GameSystem
** File description:
** GameSystem
*/

#include "RTypeGameSystem.hpp"
#include "Storage.hpp"

namespace rtype {

    RTypeGameSystem::RTypeGameSystem(std::vector<std::shared_ptr<IScene>> &scenes) : AGameSystem("RType")
    {
    }

    RTypeGameSystem::~RTypeGameSystem()
    {
    }

    void RTypeGameSystem::init()
    {
        _startingTime = std::chrono::high_resolution_clock::now();
        _storage = Storage::getStorage();
    }

    void RTypeGameSystem::update(std::shared_ptr<IScene> &scene)
    {
        auto current = std::chrono::high_resolution_clock::now();
        int64_t elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current - _startingTime).count();
        size_t scene_id = _storage->getCurrentScene();
        size_t previous_scene_id = _storage->getPreviousScene();
        bool soundState = _storage->getSoundState();

        if (_storage->getRenderWindow().isOpen() == false)
            return;
        scene->update(elapsed_time, _storage->getWindowWidth(), _storage->getWindowHeight(), scene_id, previous_scene_id, soundState);
        if (elapsed_time >= 10000)
            _startingTime = current;
        if (soundState != _storage->getSoundState())
            _storage->setSoundState(soundState);
        if (scene_id == (size_t)-1)
            _storage->getRenderWindow().close();
        else if (scene_id != _storage->getCurrentScene()) {
            _storage->setPreviousScene(_storage->getCurrentScene());
            _storage->setCurrentScene(scene_id);
        }
    }

    bool RTypeGameSystem::isGameStillPlaying()
    {
        return _storage->getRenderWindow().isOpen() && _storage->isStillPlaying();
    }

    const size_t &RTypeGameSystem::getCurrentScene() const
    {
        return _storage->getCurrentScene();
    }
}