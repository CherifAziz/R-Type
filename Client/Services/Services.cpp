/*
** EPITECH PROJECT, 2023
** Services.cpp
** File description:
** Services
*/

#include "config.hpp"
#include <string>
#include "Services.hpp"
#include "Sprite.hpp"
#include "Animation.hpp"
#include "GameValues.hpp"
#include "UdpServerSystem.hpp"

Services::Service::Service()
{
    this->_commands.push_back(std::bind(&Services::Service::Connected, this, std::placeholders::_1, std::placeholders::_2));
    this->_commands.push_back(std::bind(&Services::Service::Disconnect, this, std::placeholders::_1, std::placeholders::_2));
    this->_commands.push_back(std::bind(&Services::Service::Move, this, std::placeholders::_1, std::placeholders::_2));
    this->_commands.push_back(std::bind(&Services::Service::Shoot, this, std::placeholders::_1, std::placeholders::_2));
    this->_commands.push_back(std::bind(&Services::Service::NewPlayer, this, std::placeholders::_1, std::placeholders::_2));
    this->_commands.push_back(std::bind(&Services::Service::PlayerDisconnected, this, std::placeholders::_1, std::placeholders::_2));
}

Services::Service::~Service()
{
}

void Services::Service::callService(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene)
{
}

void Services::Service::callService(Serialize::Data &data, rtype::IScene &scene)
{
    this->_commands[data.s_id](data, scene);
}

void createPlayer(rtype::ComponentManager &Components, rtype::EntityManager &Entities, boost::uuids::uuid uid)
{
    entity_t player = Entities.spawnEntity("player")->getId();
    Sprite spaceship_sprite(std::string(ASSETS_DIR)+"spaceship.gif", 100, 100, 4);
    Animation spaceship_animation(PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, PLAYER_X_DEFAULT_SPRITE, 0, 1, 1, 1, 1, 500);
    Network spaceship_network(uid);


    std::shared_ptr<ComponentMap<Sprite>> mapS = Components.getComponents<Sprite>();
    std::shared_ptr<ComponentMap<Animation>> mapA = Components.getComponents<Animation>();
    std::shared_ptr<ComponentMap<Network>> mapN = Components.getComponents<Network>();

    mapS->put(spaceship_sprite, player);
    mapA->put(spaceship_animation, player);
    mapN->put(spaceship_network, player);
    return;
}

std::vector<std::string> parseData(std::string data)
{
    std::vector<std::string> part;
    size_t pos = 0;

    while ((pos = data.find("\t")) != std::string::npos) {
        part.push_back(data.substr(0, pos));
        data.erase(0, pos + 1);
    }

    for (auto &i : part) {
        std::cout << i << std::endl;
    }

    return part;
}

void Services::Service::Connected(Serialize::Data &data, rtype::IScene &scene) {
    std::cout << "connected" << std::endl;
    data.printData();
    std::vector<std::string> datas = parseData(data._data);
    int index = 0;

    for (auto &i : datas) {
        if (index == datas.size() - 1) {
            Network network(boost::lexical_cast<boost::uuids::uuid>(i));
            std::shared_ptr<ComponentMap<Network>> mapN = scene.getComponentManager().getComponents<Network>();
            mapN->put(network, scene.getEntityManager().getEntitiesFromFamily("player")[0]->getId());
        } else {
            createPlayer(scene.getComponentManager(), scene.getEntityManager(), boost::lexical_cast<boost::uuids::uuid>(i));
        }
        index++;
    }
}

void Services::Service::Disconnect( Serialize::Data &data, rtype::IScene &scene) {
    std::cout << "disconnect" << std::endl;
}

void Services::Service::Move( Serialize::Data &data, rtype::IScene &scene) {
    std::cout << "move" << std::endl;
}

void Services::Service::Shoot( Serialize::Data &data, rtype::IScene &scene) {
    std::cout << "shoot" << std::endl;
}

void Services::Service::NewPlayer(Serialize::Data &data, rtype::IScene &scene) {
    createPlayer(scene.getComponentManager(), scene.getEntityManager(), boost::lexical_cast<boost::uuids::uuid>(data._data));
}

void Services::Service::PlayerDisconnected(Serialize::Data &data, rtype::IScene &scene) {
    std::cout << "player disconnected" << std::endl;

    std::vector<std::shared_ptr<rtype::Entity>> players = scene.getEntityManager().getEntitiesFromFamily("player");
    std::shared_ptr<ComponentMap<Network>> mapN = scene.getComponentManager().getComponents<Network>();
    try {
        boost::uuids::uuid uuid = boost::lexical_cast<boost::uuids::uuid>(data._data);

        for (auto &i : players) {
            if (mapN->get(i->getId()).getUUID() == uuid) {
                std::cout << "Entity removed" << i->getId() << std::endl;
                scene.getEntityManager().killEntity(i->getId());
                scene.getComponentManager().killEntity(i->getId());
                break;
            }
        }
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}