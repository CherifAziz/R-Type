/*
** EPITECH PROJECT, 2023
** AGameSystem
** File description:
** AGameSystem
*/

#include "AGameSystem.hpp"

namespace rtype {

    AGameSystem::AGameSystem(const std::string &name) : _name(name)
    {
    }

    const std::string &AGameSystem::getName() const
    {
        return _name;
    }    
}