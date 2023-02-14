/*
** EPITECH PROJECT, 2023
** Core
** File description:
** Core
*/
#include "Core.hpp"

#include "SfmlInputSystem.hpp"
#include "SfmlRenderSystem.hpp"
#include "RTypeGameSystem.hpp"

namespace rtype
{
    Core::Core()
    {
        _systems.push_back(std::make_shared<SfmlInputSystem>());
        _systems.push_back(std::make_shared<SfmlRenderSystem>());
        _systems.push_back(std::make_shared<RTypeGameSystem>());

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
        std::pair<size_t, size_t> window_size;

        srand(time(NULL));
        while (isGameRunning()) {
            ComponentManager componentManager;
            EntityManager entityManager;

            for (auto &system : _systems)
                system->update(componentManager, entityManager);
        }
        return 0;
    }

    const bool &Core::isGameRunning() const
    {
        for (auto &system : _systems)
            if (system->isGameStillPlaying() == false)
                return true;
    }

    ComponentManager &Core::getComponentManager() const
    {
        for (auto &system : _systems) {
            RTypeGameSystem &game = static_cast<RTypeGameSystem &>(system);

            if (game) {
                return (game.getComponentManager());
            }
        }
    }

    EntityManager &Core::getEntityManager() const
    {
        for (auto &system : _systems) {
            RTypeGameSystem &game = static_cast<RTypeGameSystem &>(system);

            if (game) {
                return (game.getEntityManager());
            }
        }
    }
}