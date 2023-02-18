/*
** EPITECH PROJECT, 2023
** Services.cpp
** File description:
** Services
*/

#include "Services.hpp"
#include "Sprite.hpp"
#include "Animation.hpp"
#include "GameValues.hpp"
#include <string>

Services::Service::Service(): AService()
{
    this->_commands.push_back(std::bind(&Services::Service::Connected, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    this->_commands.push_back(std::bind(&Services::Service::Disconnect, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    this->_commands.push_back(std::bind(&Services::Service::Move, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    this->_commands.push_back(std::bind(&Services::Service::Shoot, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    this->_notifs.push_back(std::bind(&Services::Service::NewPlayer, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    this->_notifs.push_back(std::bind(&Services::Service::PlayerMove, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
}

Services::Service::~Service()
{
}

void Services::Service::Connected(std::map<udp::endpoint, std::unique_ptr<UdpClient>> &clients, Serialize::Data &data, ComponentManager &Components, EntityManager &Entities) {
    std::cout << "connected" << std::endl;
    Sprite spaceship_sprite("assets/spaceship.gif", 100, 100, 4);
    Animation spaceship_animation(PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, PLAYER_X_DEFAULT_SPRITE, 0, 1, 1, 1, 1, 500);

    std::shared_ptr<ComponentMap<Sprite>> mapS = Components.getComponents<Sprite>();
    std::shared_ptr<ComponentMap<Animation>> mapA = Components.getComponents<Animation>();

    mapS->put(spaceship_sprite, Entities.spawnEntity("player2")->getId());
    mapA->put(spaceship_animation, Entities.getEntitiesFromFamily("player2")[0]->getId());
}

void Services::Service::Disconnect(std::map<udp::endpoint, std::unique_ptr<UdpClient>> &clients, Serialize::Data &data, ComponentManager &Components, EntityManager &Entities) {
    std::cout << "disconnect" << std::endl;
}

void Services::Service::Move(std::map<udp::endpoint, std::unique_ptr<UdpClient>> &clients, Serialize::Data &data, ComponentManager &Components, EntityManager &Entities) {
    std::cout << "move" << std::endl;
}

void Services::Service::Shoot(std::map<udp::endpoint, std::unique_ptr<UdpClient>> &clients, Serialize::Data &data, ComponentManager &Components, EntityManager &Entities) {
    std::cout << "shoot" << std::endl;
}

void Services::Service::NewPlayer(std::map<udp::endpoint, std::unique_ptr<UdpClient>> &clients, Serialize::Data &data, ComponentManager &Components, EntityManager &Entities) {
    std::cout << "new player" << std::endl;
}

void Services::Service::PlayerMove(std::map<udp::endpoint, std::unique_ptr<UdpClient>> &clients, Serialize::Data &data, ComponentManager &Components, EntityManager &Entities) {
    std::cout << "player move" << std::endl;
}