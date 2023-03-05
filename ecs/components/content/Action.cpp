/*
** EPITECH PROJECT, 2023
** Action
** File description:
** Action
*/

#include "Action.hpp"

namespace rtype {

    Action::Action()
    {
    }

    Action::~Action()
    {
    }

    void Action::setState(const KeyType &key, const KeyState &state)
    {
        _keys[key] = state;
    }
}