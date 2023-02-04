/*
** EPITECH PROJECT, 2023
** Core.cpp
** File description:
** Core file
*/

#include "Core.hpp"

Core::Core(sf::RenderWindow &tempWindow) : window(tempWindow)
{
    this->window.setFramerateLimit(60);
}

Core::~Core()
{

}

void Core::setWindow(sf::VideoMode windowSize, const sf::String &windowName, sf::Uint32 windowStyle)
{
    this->window.create(windowSize, windowName, windowStyle);
}

int Core::mainLoop()
{
    while (this->window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            
        }

        this->window.clear();

        this->window.display();
    }

    return 0;
}