#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Ma fenêtre SFML");
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
    window.clear();
    window.display();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 0;
}