/*
** EPITECH PROJECT, 2023
** Sprite
** File description:
** Sprite
*/

#include "Sprite.hpp"

namespace rtype {

    Sprite::Sprite(const std::string &filename = "", const int &x = 0, const int &y = 0, const size_t &scale = 1) : _filename(filename), _x(x), _y(y), _scale(scale)
    {
    }

    Sprite::~Sprite()
    {
    }

    void Sprite::setPosition(const int &x, const int &y)
    {
        _x = x;
        _y = y;
    }
}