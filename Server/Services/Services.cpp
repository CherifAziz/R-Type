/*
** EPITECH PROJECT, 2023
** Services.cpp
** File description:
** Services
*/

#include <string>
#include "Services.hpp"
#include "Sprite.hpp"
#include "Network.hpp"
#include "Animation.hpp"
#include "GameValues.hpp"
#include "UdpServerSystem.hpp"

Services::Service::Service()
{
    this->_commands.push_back(std::bind(&Services::Service::Connected, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    this->_commands.push_back(std::bind(&Services::Service::Disconnect, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    this->_commands.push_back(std::bind(&Services::Service::Move, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    this->_commands.push_back(std::bind(&Services::Service::Shoot, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
}

Services::Service::~Service()
{
}

void Services::Service::callService(udp::endpoint &client, std::map<udp::endpoint, std::unique_ptr<UdpClient>> &clients, Serialize::Data &data, rtype::IScene &scene)
{
    this->_commands[data.s_id](client, clients, data, scene);
}

void Services::Service::callService(Serialize::Data &data, rtype::IScene &scene)
{
}

boost::uuids::uuid createPlayer(rtype::ComponentManager &Components, rtype::EntityManager &Entities)
{
    entity_t player = Entities.spawnEntity("player")->getId();
    Sprite spaceship_sprite("assets/spaceship.gif", 100, 100, 4);
    Animation spaceship_animation(PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, PLAYER_X_DEFAULT_SPRITE, 0, 1, 1, 1, 1, 500);
    Network spaceship_network;

    std::shared_ptr<ComponentMap<Sprite>> mapS = Components.getComponents<Sprite>();
    std::shared_ptr<ComponentMap<Animation>> mapA = Components.getComponents<Animation>();
    std::shared_ptr<ComponentMap<Network>> mapN = Components.getComponents<Network>();

    mapS->put(spaceship_sprite, player);
    mapA->put(spaceship_animation, player);
    mapN->put(spaceship_network, player);
    return spaceship_network.getUUID();
}

void Services::Service::Connected(udp::endpoint &client, std::map<udp::endpoint, std::unique_ptr<UdpClient>> &clients, Serialize::Data &data, rtype::IScene &scene) {
    std::cout << "connected" << std::endl;
    std::string uid_player = boost::uuids::to_string(createPlayer(scene.getComponentManager(), scene.getEntityManager()));
    std::string uid;

    std::vector<std::shared_ptr<rtype::Entity>> entities = scene.getEntityManager().getEntitiesFromFamily("player");

    for (auto &entity : entities) {
        uid.append(boost::uuids::to_string(scene.getComponentManager().getComponents<Network>()->get(entity->getId()).getUUID()));
        uid.append("\t");
    }

    std::cout << "uid players => " << uid << std::endl;
    std::cout << "uid player => " << uid_player << std::endl;

    for (auto &clientTmp : clients)
        if (clientTmp.first == client)
            clientTmp.second->sendDataToClient(Serialize::createData<Serialize::Data>(Services::Command::CONNECTED, uid));
        else
            clientTmp.second->sendDataToClient(Serialize::createData<Serialize::Data>(Services::Command::NEW_PLAYER, uid_player));

}

void Services::Service::Disconnect(udp::endpoint &client, std::map<udp::endpoint, std::unique_ptr<UdpClient>> &clients, Serialize::Data &data, rtype::IScene &scene) {
    std::cout << "disconnect" << std::endl;
}

void Services::Service::Move(udp::endpoint &client, std::map<udp::endpoint, std::unique_ptr<UdpClient>> &clients, Serialize::Data &data, rtype::IScene &scene) {
    std::cout << "move" << std::endl;
}

void Services::Service::Shoot(udp::endpoint &client, std::map<udp::endpoint, std::unique_ptr<UdpClient>> &clients, Serialize::Data &data, rtype::IScene &scene) {
    std::cout << "shoot" << std::endl;
}

void Services::Service::NewPlayer(udp::endpoint &client, std::map<udp::endpoint, std::unique_ptr<UdpClient>> &clients, Serialize::Data &data, rtype::IScene &scene) {
    std::cout << "new player" << std::endl;
}

void Services::Service::PlayerMove(udp::endpoint &client, std::map<udp::endpoint, std::unique_ptr<UdpClient>> &clients, Serialize::Data &data, rtype::IScene &scene) {
    std::cout << "player move" << std::endl;
}