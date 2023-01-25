/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main
*/

#include "Core.hpp"

int main(void)
{
    sf::RenderWindow tempWindow(sf::VideoMode(1500, 800), "R-TYPE", sf::Style::Default);
    Core core(tempWindow);

    core.mainLoop();
}