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

Services::Service::Service()
{
    this->_commands.push_back(std::bind(&Services::Service::Connected, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    this->_commands.push_back(std::bind(&Services::Service::Disconnect, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    this->_commands.push_back(std::bind(&Services::Service::Move, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    this->_commands.push_back(std::bind(&Services::Service::Shoot, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    this->_commands.push_back(std::bind(&Services::Service::NewPlayer, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    this->_commands.push_back(std::bind(&Services::Service::PlayerDisconnected, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    this->_commands.push_back(std::bind(&Services::Service::MovePlayer, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
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

void createPlayer(rtype::ComponentManager &Components, rtype::EntityManager &Entities, boost::uuids::uuid uid)
{
    std::cout << "create Player" << std::endl;
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

void Services::Service::Connected(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene) {
    std::cout << "connected" << std::endl;
    data.printData();
    std::vector<std::string> datas = parseData(data._data);
    int index = 0;

    for (auto &i : datas) {
        std::cout << index << std::endl;
        if (index == datas.size() - 1) {
            std::cout << "add network to current player" << std::endl;
            Network network(boost::lexical_cast<boost::uuids::uuid>(i));
            std::cout << "Zebi 1" << std::endl;
            std::shared_ptr<ComponentMap<Network>> mapN = scene.getComponentManager().getComponents<Network>();
            std::cout << "Zebi 2" << std::endl;
            mapN->put(network, scene.getEntityManager().getEntitiesFromFamily("player")[0]->getId());
            std::cout << "Zebi 3" << std::endl;
        } else {
            std::cout << "new Player" << std::endl;
            createPlayer(scene.getComponentManager(), scene.getEntityManager(), boost::lexical_cast<boost::uuids::uuid>(i));
        }
        index++;
    }
    std::cout << "end of connected function" << std::endl;
}

void Services::Service::Disconnect( Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene) {
    std::cout << "disconnect" << std::endl;
}

void Services::Service::Move(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene) {
    client.send_data(data.s_id, data._data);
}

void Services::Service::Shoot(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene) {
    std::cout << "shoot" << std::endl;
}

void Services::Service::NewPlayer(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene) {
    createPlayer(scene.getComponentManager(), scene.getEntityManager(), boost::lexical_cast<boost::uuids::uuid>(data._data));
}

void Services::Service::PlayerDisconnected(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene) {
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

void Services::Service::MovePlayer(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene) {
    std::vector<std::string> datas = parseData(data._data);
    std::vector<std::shared_ptr<rtype::Entity>> players = scene.getEntityManager().getEntitiesFromFamily("player");
    std::shared_ptr<ComponentMap<Network>> mapN = scene.getComponentManager().getComponents<Network>();
    std::shared_ptr<ComponentMap<Action>> mapA = scene.getComponentManager().getComponents<Action>();
    try {
        boost::uuids::uuid uuid = boost::lexical_cast<boost::uuids::uuid>(datas[0]);

        for (auto &i : players) {
            if (mapN->get(i->getId()).getUUID() == uuid) {
                std::cout << "move played" << std::endl;
                mapA->get(i->getId()).setState(rtype::Action::KeyType(std::stoi(datas[1])), rtype::Action::KeyState(std::stoi(datas[2])));
                break;
            }
        }
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}