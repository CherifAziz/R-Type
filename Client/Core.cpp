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

#include "GameScene/GameScene.hpp"

#include "SfmlInputSystem.hpp"
#include "SfmlRenderSystem.hpp"
#include "TcpClientSystem.hpp"
#include "Services.hpp"

Core::Core(boost::asio::io_context &ioc, std::string ip, std::string port) : _timer(ioc)
{
    _systems.push_back(std::make_shared<SfmlInputSystem>());
    _systems.push_back(std::make_shared<SfmlRenderSystem>());
    _systems.push_back(std::make_shared<RTypeGameSystem>(this->_scenes));
    _systems.push_back(std::make_shared<TcpClientSystem>(ioc, ip, std::atoi(port.c_str()), std::make_shared<Services::Service>()));
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
    if (this->isGameRunning()) {
        this->_timer.expires_after(std::chrono::milliseconds(1000 / 60));
        this->_timer.async_wait(boost::bind(&Core::loopGame, this));
        for (auto &system : _systems) {
            system->update(_scenes[system->getCurrentScene()]);
        }
    } else {
        for (auto &system : this->_systems)
            system->destroy();
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