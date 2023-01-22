/*
** EPITECH PROJECT, 2023
** exo3
** File description:
** exo3
*/

#include <SFML/Graphics.hpp>

#include "components/container/ComponentManager.hpp"

#include "components/content/Movement.hpp"
#include "components/content/Render.hpp"

void render_game(sf::RenderWindow &window, const std::shared_ptr<ComponentMap<Render>> &render)
{
    window.clear();
    for (int it = 0; it < render->get_size(); it++) {
        Render element = render->get(it);
        sf::Texture texture;
        sf::Sprite sprite;

        texture.loadFromFile(element.get_filename());
        sprite.setTexture(texture);
        // std::cout << "GET " << element.get_x() << " " << element.get_y() << std::endl;
        sprite.setPosition(element.get_x(), element.get_y());
        window.draw(sprite);
    }
    window.display();
}

ComponentMap<Render> init_render(const entity_t &player)
{
    ComponentMap<Render> render;
    Render player_render("alacritty_logo.png", 20, 20);

    render.put(player_render, player);
    return render;
}

ComponentMap<Movement> init_movement(const entity_t &player)
{
    ComponentMap<Movement> movement;
    Movement player_movement(10, 10);

    movement.put(player_movement, player);
    return movement;
}

void handle_input_event(sf::Event &event, std::shared_ptr<ComponentMap<Render>> render, std::shared_ptr<ComponentMap<Movement>> movement, entity_t &player,
std::unordered_map<sf::Keyboard::Key, bool> &keys_status)
{
    Render &player_render = render->get(player);
    Movement &player_movement = movement->get(player);
    sf::Keyboard::Key key = event.key.code;

    for (auto &value : keys_status) {
        if (key == value.first)
            value.second = event.type == sf::Event::KeyPressed ? true : false;
    }

    if (keys_status[sf::Keyboard::Z])
        player_render.set_position(player_render.get_x(), player_render.get_y() - player_movement.get_yDirection());
    if (keys_status[sf::Keyboard::S])
        player_render.set_position(player_render.get_x(), player_render.get_y() + player_movement.get_yDirection());
    if (keys_status[sf::Keyboard::Q])
        player_render.set_position(player_render.get_x() - player_movement.get_xDirection(), player_render.get_y());
    if (keys_status[sf::Keyboard::D])
        player_render.set_position(player_render.get_x() + player_movement.get_xDirection(), player_render.get_y());
}

int main(void)
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Please move");
    sf::Event event;
    ComponentManager manager;
    entity_t player = 0;
    std::unordered_map<sf::Keyboard::Key, bool> keys_status;

    player = manager.spawn_entity();
    manager.register_component<Render>(init_render(player));
    manager.register_component<Movement>(init_movement(player));
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
                handle_input_event(event, manager.get_components<Render>(), manager.get_components<Movement>(), player, keys_status);
        }
        render_game(window, manager.get_components<Render>());
        
    }
    return 0;
}