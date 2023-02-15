/*
** EPITECH PROJECT, 2023
** Core
** File description:
** Core
*/

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
            for (auto &system : _systems)
                system->update(_scenes[system->getCurrentScene()]);
        }
        return 0;
    }

    bool Core::isGameRunning()
    {
        for (auto &system : _systems)
            if (system->isGameStillPlaying() == false)
                return true;
        return false;
    }
}