/*
** EPITECH PROJECT, 2023
** Core
** File description:
** Core
*/

#include <chrono>

#include "Core.hpp"

#include "GameScene/GameScene.hpp"
#include "GameScene/HomeMenuScene.hpp"

#include "SfmlInputSystem.hpp"
#include "SfmlRenderSystem.hpp"
#include "RTypeGameSystem.hpp"

#include "Core.hpp"

namespace rtype
{
    Core::Core()
    {
        _systems.push_back(std::make_shared<SfmlInputSystem>());
        _systems.push_back(std::make_shared<SfmlRenderSystem>());
        _systems.push_back(std::make_shared<RTypeGameSystem>(_scenes));

        for (auto &system : _systems)
            system->init();
    }

    Core::~Core()
    {
        for (auto &system : _systems)
            system->destroy();
    }

    int Core::loopGame()
    {
        srand(time(NULL));
        while (isGameRunning()) {
            for (auto &system : _systems) {
                size_t current_scene = system->getCurrentScene();

                system->update(_scenes[current_scene]);
                if (current_scene != system->getCurrentScene()) {
                    clearSystemCache();
                    break;
                }
            }
        }
        return 0;
    }

    bool Core::isGameRunning()
    {
        for (auto &system : _systems)
            if (system->isGameStillPlaying() == false)
                return false;
        return true;
    }

    void Core::clearSystemCache()
    {
        for (auto &system : _systems)
            system->destroy();
    }
}