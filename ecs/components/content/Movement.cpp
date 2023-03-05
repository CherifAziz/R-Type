/*
** EPITECH PROJECT, 2023
** Movement
** File description:
** Movement
*/

#include "Movement.hpp"

namespace rtype {

    Movement::Movement(const float &xDirection, const float &yDirection) : _xDirection(xDirection), _yDirection(yDirection)
    {
    }

    Movement::~Movement()
    {
    }

    void Movement::setDirection(const float &xDirection, const float &yDirection)
    {
        _xDirection = xDirection;
        _yDirection = yDirection;
    }

    bool Movement::operator==(const Movement &other) const
    {
        return _xDirection == other._xDirection && _yDirection == other._yDirection;
    }
}