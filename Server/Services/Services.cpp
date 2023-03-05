/*
** EPITECH PROJECT, 2023
** Services.cpp
** File description:
** Services
*/

#include <string>
#include <utility>
#include "Network.hpp"
#include "Services.hpp"
#include "Collision.hpp"
#include "GameValues.hpp"
#include "UdpServerSystem.hpp"

Services::Service::Service()
{
    this->_commands.push_back(std::bind(&Services::Service::Connected, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    this->_commands.push_back(std::bind(&Services::Service::Disconnect, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    this->_commands.push_back(std::bind(&Services::Service::Useless, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    this->_commands.push_back(std::bind(&Services::Service::Useless, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    this->_commands.push_back(std::bind(&Services::Service::Useless, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    this->_commands.push_back(std::bind(&Services::Service::Useless, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    this->_commands.push_back(std::bind(&Services::Service::NewEnemy, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
}

Services::Service::~Service()
{
}

entity_t Services::Service::callService(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene)
{
    this->_commands[data.s_id](client, clients, data, scene);
}

entity_t Services::Service::callService(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene)
{
}

std::pair<boost::uuids::uuid, entity_t> createPlayer(rtype::ComponentManager &Components, rtype::EntityManager &Entities)
{
    entity_t player = Entities.spawnEntity("player")->getId();
    Network spaceship_network;
    Collision spaceship_collision({
        "basicEnemy",
        "mediumEnemy",
        "vesselEnemy",
        "flyEnemy",
        "boss"
    });
    Sprite spaceship_sprite("assets/spaceship.gif", 100, 100, 4);
    Animation spaceship_animation(PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, PLAYER_X_DEFAULT_SPRITE, 0, 1, 1, 1, 1, 500);
    Action spaceship_action;
    Movement spaceship_movement;


    
    std::shared_ptr<ComponentMap<Collision>> mapC = Components.getComponents<Collision>();
    std::shared_ptr<ComponentMap<Network>> mapN = Components.getComponents<Network>();
    std::shared_ptr<ComponentMap<Sprite>> mapS = Components.getComponents<Sprite>();
    std::shared_ptr<ComponentMap<Animation>> mapA = Components.getComponents<Animation>();
    std::shared_ptr<ComponentMap<Movement>> mapM = Components.getComponents<Movement>();
    std::shared_ptr<ComponentMap<Action>> mapAc = Components.getComponents<Action>();
    
    mapC->put(spaceship_collision, player);
    mapN->put(spaceship_network, player);
    mapS->put(spaceship_sprite, player);
    mapA->put(spaceship_animation, player);
    mapAc->put(spaceship_action, player);
    mapM->put(spaceship_movement, player);
    return std::make_pair(spaceship_network.getUUID(), player);
}

entity_t Services::Service::Connected(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene) {
    std::pair<boost::uuids::uuid, entity_t> player_pair = createPlayer(scene.getComponentManager(), scene.getEntityManager());
    std::vector<std::string> uid;
    std::vector<std::shared_ptr<rtype::Entity>> entities = scene.getEntityManager().getEntitiesFromFamily("player");

    for (auto &entity : entities) {
        uid.push_back(boost::uuids::to_string(scene.getComponentManager().get<Network>(entity->getId()).getUUID()));
    }
    if (clients.getClient(client).has_value()) {
        clients.getClient(client).value()->setUuid(player_pair.first);
        clients.getClient(client).value()->setEntity(player_pair.second);
    }
    for (auto &clientTmp : clients.getClients())
        if (clientTmp.first == client) {
            clientTmp.second->sendDataToClient(Serialize::createData<Serialize::Data>(Services::Command::CONNECTED, uid));
        }
        else {
            clientTmp.second->sendDataToClient(Serialize::createData<Serialize::Data>(Services::Command::NEW_PLAYER, { boost::uuids::to_string((player_pair.first)) }));
        }
}

entity_t Services::Service::Disconnect(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene) {
    std::shared_ptr<ComponentMap<Network>> mapN = scene.getComponentManager().getComponents<Network>();
    boost::uuids::uuid uuid = clients.getClient(client).value()->getUuid();
    scene.getEntityManager().killEntity(clients.getClient(client).value()->getEntity());
    scene.getComponentManager().killEntity(clients.getClient(client).value()->getEntity());
    clients.removeClient(client);
    clients.sendToEachClient(Serialize::createData<Serialize::Data>(Services::Command::PLAYER_DISCONNECTED, { boost::uuids::to_string(uuid) }));
}

entity_t Services::Service::Move(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene) {
    for (auto &clientTmp : clients.getClients())
        if (clientTmp.first != client)
            clientTmp.second->sendDataToClient(Serialize::createData<Serialize::Data>(Services::Command::EVENT_PLAYER, data._args));
}

entity_t Services::Service::NewPlayer(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene) {
    std::cout << "new player" << std::endl;
}

entity_t Services::Service::NewEnemy(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene) {
    // std::cout << "new enemy" << std::endl;
    clients.getClients().at(client)->sendDataToClient(data);
}

entity_t Services::Service::Useless(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene) {}

entity_t Services::Service::PlayerMove(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene) {
    std::cout << "player move" << std::endl;
}