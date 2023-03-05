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
        scenes.push_back(std::make_shared<GameScene>());
    }

    RTypeGameSystem::~RTypeGameSystem()
    {
    }

    void RTypeGameSystem::init()
    {
        _startingTime = std::chrono::steady_clock::now();
        _storage = Storage::getStorage();
    }

    void RTypeGameSystem::update(std::shared_ptr<IScene> &scene)
    {
        auto current = std::chrono::steady_clock::now();
        int64_t elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current - _startingTime).count();
        if (_storage->getRenderWindow().isOpen() == false)
            return;
        scene->update(elapsed_time, _storage->getWindowWidth(), _storage->getWindowHeight());
        if (elapsed_time >= 100)
            _startingTime = current;
    }

    bool RTypeGameSystem::isGameStillPlaying()
    {
        return _storage->getRenderWindow().isOpen();
    }

    const size_t &RTypeGameSystem::getCurrentScene() const
    {
        return _storage->getCurrentScene();
    }
}