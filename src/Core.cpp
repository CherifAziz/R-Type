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

namespace rtype
{
    Core::Core(size_t defaultScene) : _currentScene(defaultScene)
    {
        _scenes.push_back(std::make_shared<GameScene>());
        _systems.push_back(std::make_shared<SfmlInputSystem>());
        _systems.push_back(std::make_shared<SfmlRenderSystem>());

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
        auto starting_time = std::chrono::high_resolution_clock::now();
        std::chrono::high_resolution_clock::time_point current;
        int64_t elapsed_time = 0;

        while (_scenes[_currentScene]->isGameStillPlaying()) {
            current = std::chrono::high_resolution_clock::now();
            elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current - starting_time).count();
            _scenes[_currentScene]->update(elapsed_time);
            if (elapsed_time >= 50)
                starting_time = current;
            for (auto &system : _systems)
                system->update(_scenes[_currentScene]->getComponentManager(), _scenes[_currentScene]->getEntityManager());
        }
        return 0;
    }
}