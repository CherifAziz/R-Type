/*
** EPITECH PROJECT, 2023
** Animation
** File description:
** Animation
*/

#include "Animation.hpp"

namespace rtype {

    Animation::Animation(const size_t &rectWidth, const size_t &rectHeight, const size_t &x, const size_t &y, const size_t &horizontalPictureNb,
                const size_t &verticalPictureNb, const size_t &horizontalSeparator, const size_t &verticalSeparator, const size_t &delay) :
                _rectWidth(rectWidth), _rectHeight(rectHeight), _x(x), _y(y), _horizontalPictureNb(horizontalPictureNb), _verticalPictureNb(verticalPictureNb),
                _horizontalSeparator(horizontalSeparator), _verticalSeparator(verticalSeparator), _delay(delay), _defaultX(x), _defaultY(y)
    {
    }

    Animation::~Animation()
    {
    }

    void Animation::animate()
    {
        if (_horizontalPictureNb == 1 && _verticalPictureNb == 1)
            return;
        _x += _rectWidth + _horizontalSeparator;
        if (_x > _defaultX + (_horizontalPictureNb - 1) * (_rectWidth + _horizontalSeparator)) {
            _x = _defaultX;
            _y += _rectHeight + _verticalSeparator;
            if (_y > _defaultY + (_verticalPictureNb - 1) * (_rectHeight + _verticalSeparator)) {
                _x = _defaultX;
                _y = _defaultY;
            }
        }
    }

    bool Animation::operator==(const Animation &other) const
    {
        return _rectWidth == other._rectWidth && _rectHeight == other._rectHeight && _x == other._x && _y == other._y
        && _horizontalPictureNb == other._horizontalPictureNb && _verticalPictureNb == other._verticalPictureNb
        && _horizontalSeparator == other._horizontalSeparator && _verticalSeparator == other._verticalSeparator && _delay == other._delay
        && _defaultX == other._defaultX && _defaultY == other._defaultY;
    }

    Animation &Animation::operator=(const Animation &other)
    {
        _rectWidth = other._rectWidth;
        _rectHeight = other._rectHeight;
        _x = other._x;
        _y = other._y;
        _horizontalPictureNb = other._horizontalPictureNb;
        _verticalPictureNb = other._verticalPictureNb;
        _horizontalSeparator = other._horizontalSeparator;
        _verticalSeparator = other._verticalSeparator;
        _delay = other._delay;
        _defaultX = other._defaultX;
        _defaultY = other._defaultY;
        return *this;
    }
}