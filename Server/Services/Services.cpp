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
#include <utility>

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

void Services::Service::callService(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene)
{
    std::cout << "call service" << std::endl;
    this->_commands[data.s_id](client, clients, data, scene);
}

void Services::Service::callService(Serialize::Data &data, rtype::IScene &scene)
{
}

std::pair<boost::uuids::uuid, entity_t> createPlayer(rtype::ComponentManager &Components, rtype::EntityManager &Entities)
{
    std::cout << "create player" << std::endl;
    entity_t player = Entities.spawnEntity("player")->getId();
    Network spaceship_network;

    std::shared_ptr<ComponentMap<Sprite>> mapS = Components.getComponents<Sprite>();
    std::shared_ptr<ComponentMap<Animation>> mapA = Components.getComponents<Animation>();
    std::shared_ptr<ComponentMap<Network>> mapN = Components.getComponents<Network>();

    mapN->put(spaceship_network, player);
    return std::make_pair(spaceship_network.getUUID(), player);
    std::cout << "End of create player" << std::endl;
}

void Services::Service::Connected(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene) {
    std::cout << "connected Zebi " << std::endl;
    std::pair<boost::uuids::uuid, entity_t> player_pair = createPlayer(scene.getComponentManager(), scene.getEntityManager());
    std::string uid;

    std::vector<std::shared_ptr<rtype::Entity>> entities = scene.getEntityManager().getEntitiesFromFamily("player");

    for (auto &entity : entities) {
        uid.append(boost::uuids::to_string(scene.getComponentManager().getComponents<Network>()->get(entity->getId()).getUUID()));
        uid.append("\t");
    }

    std::cout << "uid players => " << uid << std::endl;
    std::cout << "uid player => " << player_pair.first << std::endl;

    if (clients.getClient(client).has_value()) {
        clients.getClient(client).value()->setUuid(player_pair.first);
        clients.getClient(client).value()->setEntity(player_pair.second);
    }

    for (auto &clientTmp : clients.getClients())
        if (clientTmp.first == client)
            clientTmp.second->sendDataToClient(Serialize::createData<Serialize::Data>(Services::Command::CONNECTED, uid));
        else
            clientTmp.second->sendDataToClient(Serialize::createData<Serialize::Data>(Services::Command::NEW_PLAYER, boost::uuids::to_string((player_pair.first))));

}

void Services::Service::Disconnect(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene) {
    std::cout << "disconnect" << std::endl;
    std::shared_ptr<ComponentMap<Network>> mapN = scene.getComponentManager().getComponents<Network>();

    boost::uuids::uuid uuid = clients.getClient(client).value()->getUuid();
    std::cout << "uuid => " << uuid << std::endl;
    scene.getEntityManager().killEntity(clients.getClient(client).value()->getEntity());
    scene.getComponentManager().killEntity(clients.getClient(client).value()->getEntity());
    clients.removeClient(client);
    clients.sendToEachClient(Serialize::createData<Serialize::Data>(Services::Command::PLAYER_DISCONNECTED, boost::uuids::to_string(uuid)));
    std::cout << "disconnect" << std::endl;
}

void Services::Service::Move(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene) {
    std::cout << "move" << std::endl;
}

void Services::Service::Shoot(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene) {
    std::cout << "shoot" << std::endl;
}

void Services::Service::NewPlayer(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene) {
    std::cout << "new player" << std::endl;
}

void Services::Service::PlayerMove(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene) {
    std::cout << "player move" << std::endl;
}