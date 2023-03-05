/*
** EPITECH PROJECT, 2023
** AServerSystem
** File description:
** AServerSystem
*/

#include "ATcpServerSystem.hpp"

namespace rtype {

    ATcpServerSystem::ATcpServerSystem(const std::string &libraryName) : _libraryName(libraryName)
    {
    }

    const std::string &ATcpServerSystem::getLibraryName() const
    {
        return _libraryName;
    }
}