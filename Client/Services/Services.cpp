/*
** EPITECH PROJECT, 2023
** Services.cpp
** File description:
** Services
*/

#include <string>
#include "Services.hpp"
#include "Sprite.hpp"
#include "Animation.hpp"
#include "Action.hpp"
#include "GameValues.hpp"
#include "UdpServerSystem.hpp"
#include "UdpClientSystem.hpp"

std::vector<std::string> ENEMIES = {
    "basicEnemy",
    "bossEnemy",
    "flyEnemy",
    "mediumEnemy",
    "vesselEnemy"
};

Services::Service::Service()
{
    this->_commands.push_back(std::bind(&Services::Service::Connected, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    this->_commands.push_back(std::bind(&Services::Service::Disconnect, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    this->_commands.push_back(std::bind(&Services::Service::Move, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    this->_commands.push_back(std::bind(&Services::Service::NewPlayer, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    this->_commands.push_back(std::bind(&Services::Service::PlayerDisconnected, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    this->_commands.push_back(std::bind(&Services::Service::MovePlayer, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    this->_commands.push_back(std::bind(&Services::Service::NewEnemy, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

Services::Service::~Service()
{
}

void Services::Service::callService(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene)
{
}

void Services::Service::callService(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene)
{
    this->_commands[data.s_id](data, client, scene);
}

void Services::Service::createPlayer(rtype::ComponentManager &Components, rtype::EntityManager &Entities, boost::uuids::uuid uid)
{
    entity_t player = Entities.spawnEntity("player")->getId();
    Sprite spaceship_sprite("assets/spaceship.gif", 100, 100, 4);
    Animation spaceship_animation(PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, PLAYER_X_DEFAULT_SPRITE, 0, 1, 1, 1, 1, 500);
    Network spaceship_network(uid);
    Action spaceship_action;
    Movement spaceship_movement(0, 0);

    std::shared_ptr<ComponentMap<Sprite>> mapS = Components.getComponents<Sprite>();
    std::shared_ptr<ComponentMap<Animation>> mapA = Components.getComponents<Animation>();
    std::shared_ptr<ComponentMap<Network>> mapN = Components.getComponents<Network>();
    std::shared_ptr<ComponentMap<Action>> mapAc = Components.getComponents<Action>();
    std::shared_ptr<ComponentMap<Movement>> mapM = Components.getComponents<Movement>();

    mapS->put(spaceship_sprite, player);
    mapA->put(spaceship_animation, player);
    mapN->put(spaceship_network, player);
    mapAc->put(spaceship_action, player);
    mapM->put(spaceship_movement, player);
    return;
}

void Services::Service::Connected(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene) {
    int index = 0;

    for (auto &i : data._args) {
        if (index == data._args.size() - 1) {
            Network network(boost::lexical_cast<boost::uuids::uuid>(i));
            std::shared_ptr<ComponentMap<Network>> mapN = scene.getComponentManager().getComponents<Network>();
            mapN->put(network, scene.getEntityManager().getEntitiesFromFamily("player")[0]->getId());
        } else {
            createPlayer(scene.getComponentManager(), scene.getEntityManager(), boost::lexical_cast<boost::uuids::uuid>(i));
        }
        index++;
    }
}

void Services::Service::createEnemy(rtype::ComponentManager &Components, rtype::EntityManager &Entities, Serialize::Data &data) {
    std::cout << "Enemy type: " << data._args[0] << std::endl;
    std::cout << "X: " << data._args[1] << std::endl;
    std::cout << "Y: " << data._args[2] << std::endl;
    // std::shared_ptr<Entity> enemy = Entities.spawnEntity(ENEMIES[std::atoi(data._args[0].c_str())]);
}

void Services::Service::Disconnect( Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene) {
    std::cout << "disconnect" << std::endl;
}

void Services::Service::Move(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene) {
    client.send_data(data);
}

void Services::Service::NewPlayer(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene) {
    createPlayer(scene.getComponentManager(), scene.getEntityManager(), boost::lexical_cast<boost::uuids::uuid>(data._args[0]));
}

void Services::Service::NewEnemy(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene) {
    createEnemy(scene.getComponentManager(), scene.getEntityManager(), data);
}

void Services::Service::PlayerDisconnected(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene) {
    std::cout << "player disconnected" << std::endl;
    std::vector<std::shared_ptr<rtype::Entity>> players = scene.getEntityManager().getEntitiesFromFamily("player");
    std::shared_ptr<ComponentMap<Network>> mapN = scene.getComponentManager().getComponents<Network>();
    try {
        boost::uuids::uuid uuid = boost::lexical_cast<boost::uuids::uuid>(data._args[0]);

        for (auto &i : players) {
            if (mapN->get(i->getId()).getUUID() == uuid) {
                scene.getEntityManager().killEntity(i->getId());
                scene.getComponentManager().killEntity(i->getId());
                break;
            }
        }
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void Services::Service::MovePlayer(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene) {
    std::vector<std::shared_ptr<rtype::Entity>> players = scene.getEntityManager().getEntitiesFromFamily("player");
    std::shared_ptr<ComponentMap<Network>> mapN = scene.getComponentManager().getComponents<Network>();
    std::shared_ptr<ComponentMap<Action>> mapA = scene.getComponentManager().getComponents<Action>();
    try {
        boost::uuids::uuid uuid = boost::lexical_cast<boost::uuids::uuid>(data._args[0]);

        for (auto &i : players) {
            if (mapN->get(i->getId()).getUUID() == uuid) {
                mapA->get(i->getId()).setState(rtype::Action::KeyType(std::stoi(data._args[1])), rtype::Action::KeyState(std::stoi(data._args[2])));
                break;
            }
        }
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}