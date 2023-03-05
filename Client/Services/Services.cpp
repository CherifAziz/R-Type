/*
** EPITECH PROJECT, 2023
** Services.cpp
** File description:
** Services
*/

#include <string>
#include "Sprite.hpp"
#include "Action.hpp"
#include "Services.hpp"
#include "Animation.hpp"
#include "Collision.hpp"
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

std::vector<Animation> ENEMIES_A = {
    Animation(20, 30, 5, 7, 8, 1, 12, 0, 500),
    Animation(255, 142, 0, 0, 2, 4, 5, 3, 2000),
    Animation(61, 46, 4, 3, 6, 1, 6, 0, 2000),
    // Animation(),
    Animation(63, 49, 1, 1, 3, 1, 2, 1, 500),
};

std::vector<Movement> ENEMIES_M = {
    Movement(-5, 3),
    Movement(1, 0),
    Movement(-2, 2),
    // Movement(),
    Movement(-5, 0)
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

entity_t Services::Service::callService(udp::endpoint &client, rtype::ClientManager &clients, Serialize::Data &data, rtype::IScene &scene)
{
}

entity_t Services::Service::callService(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene)
{
    return this->_commands[data.s_id](data, client, scene);
}

entity_t Services::Service::createPlayer(rtype::ComponentManager &Components, rtype::EntityManager &Entities, boost::uuids::uuid uid)
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
}

entity_t Services::Service::Connected(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene) {
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

entity_t Services::Service::createEnemy(rtype::ComponentManager &Components, rtype::EntityManager &Entities, Serialize::Data &data) {
    std::cout << "Enemy type: " << data._args[0] << std::endl;
    std::cout << "X: " << data._args[1] << std::endl;
    std::cout << "Y: " << data._args[2] << std::endl;
    int nbr = std::atoi(data._args[0].c_str());
    entity_t enemy = Entities.spawnEntity(ENEMIES[nbr])->getId();
    Sprite sprite = Sprite("assets/" + ENEMIES[nbr] + ".gif", std::atoi(data._args[1].c_str()), std::atoi(data._args[2].c_str()), 3);
    Animation animation = ENEMIES_A[nbr];
    Movement movement = ENEMIES_M[nbr];
    Collision collision = Collision({"player"});

    Components.put<Sprite>(sprite, enemy);
    Components.put<Animation>(animation, enemy);
    Components.put<Movement>(movement, enemy);
    Components.put<Collision>(collision, enemy);
    
    return enemy;
}

entity_t Services::Service::Disconnect( Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene) {
    std::cout << "disconnect" << std::endl;
}

entity_t Services::Service::Move(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene) {
    client.send_data(data);
}

entity_t Services::Service::NewPlayer(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene) {
    createPlayer(scene.getComponentManager(), scene.getEntityManager(), boost::lexical_cast<boost::uuids::uuid>(data._args[0]));
}

entity_t Services::Service::NewEnemy(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene) {
    createEnemy(scene.getComponentManager(), scene.getEntityManager(), data);
}

entity_t Services::Service::PlayerDisconnected(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene) {
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

entity_t Services::Service::MovePlayer(Serialize::Data &data, rtype::UdpClientSystem &client, rtype::IScene &scene) {
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