/*
** EPITECH PROJECT, 2023
** AClientSystem
** File description:
** AClientSystem
*/

#include "ATcpClientSystem.hpp"

namespace rtype {

    ATcpClientSystem::ATcpClientSystem(const std::string &libraryName) : _libraryName(libraryName)
    {
    }

    const std::string &ATcpClientSystem::getLibraryName() const
    {
        return _libraryName;
    }
}