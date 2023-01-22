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

void render_game(sf::RenderWindow &window, std::shared_ptr<ComponentMap<Render>> render)
{
    window.clear();
    for (int it = 0; it < render->get_size(); it++) {
        Render element = render->get(it);
        sf::Texture texture;
        sf::Sprite sprite;

        texture.loadFromFile(element.get_filename());
        sprite.setTexture(texture);
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

int main(void)
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Please move");
    sf::Event event;
    ComponentManager manager;
    entity_t player = 0;

    player = manager.spawn_entity();
    manager.register_component<Render>(init_render(player));
    while (window.isOpen())
    {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        render_game(window, manager.get_components<Render>());
    }
    return 0;
}