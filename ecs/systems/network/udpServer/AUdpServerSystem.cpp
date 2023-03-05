/*
** EPITECH PROJECT, 2023
** AUdpClientSystem
** File description:
** AUdpClientSystem
*/

#include "AUdpServerSystem.hpp"

namespace rtype {

    AUdpServerSystem::AUdpServerSystem(const std::string &libraryName) : _libraryName(libraryName)
    {
    }

    const std::string &AUdpServerSystem::getLibraryName() const
    {
        return _libraryName;
    }
}