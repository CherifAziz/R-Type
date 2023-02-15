/*
** EPITECH PROJECT, 2023
** Core
** File description:
** Core
*/

#include <chrono>

#include "Core.hpp"

#include "GameScene/GameScene.hpp"

#include "SfmlInputSystem.hpp"
#include "SfmlRenderSystem.hpp"
#include "ClientSystem.hpp"

namespace rtype
{
    Core::Core(size_t defaultScene, boost::asio::io_context &ioc) : _currentScene(defaultScene), _starting_time(std::chrono::high_resolution_clock::now()), _timer(ioc)
    {
        _scenes.push_back(std::make_shared<GameScene>());
        _systems.push_back(std::make_shared<SfmlInputSystem>());
        _systems.push_back(std::make_shared<SfmlRenderSystem>());
        this->_systems.push_back(std::make_shared<ClientSystem>(ioc, "127.0.0.1", 3333));

        for (auto &scene : _scenes)
            scene->init();
        for (auto &system : _systems)
            system->init();
    }

    Core::~Core()
    {
        for (auto &scene : _scenes)
            scene->destroy();
        for (auto &system : _systems)
            system->destroy();
    }

    int Core::loopGame()
    {
        int64_t elapsed_time = 0;
        std::chrono::high_resolution_clock::time_point current = std::chrono::high_resolution_clock::now();
        std::pair<size_t, size_t> window_size;

        elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current - this->_starting_time).count();
        if (this->_scenes[this->_currentScene]->isGameStillPlaying()) {
            window_size = getWindowSize();
            _scenes[_currentScene]->update(elapsed_time, window_size.first, window_size.second);
            if (elapsed_time >= 300)
                this->_starting_time = current;
            for (auto &system : _systems)
                system->update(_scenes[_currentScene]->getComponentManager(), _scenes[_currentScene]->getEntityManager());

            this->_timer.expires_after(std::chrono::milliseconds(1000 / 60));
            this->_timer.async_wait(boost::bind(&Core::loopGame, this));
        } else {
            for (auto &scene : _scenes)
                scene->destroy();
            for (auto &system : _systems)
                system->destroy();
        }
        return 0;
    }

    std::pair<size_t, size_t> Core::getWindowSize() const
    {
        for (auto &system : _systems)
            if (system->getWindowWSize().first != 0)
                return system->getWindowWSize();
        throw std::runtime_error("No system with a valid window present in the scene !");
    }
}