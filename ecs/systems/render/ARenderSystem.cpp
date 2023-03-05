/*
** EPITECH PROJECT, 2023
** ARenderSystem
** File description:
** ARenderSystem
*/

#include "ARenderSystem.hpp"

namespace rtype {

    ARenderSystem::ARenderSystem(const std::string &libraryName) : _libraryName(libraryName)
    {
    }

    const std::string &ARenderSystem::getName() const
    {
        return _libraryName;
    }
}