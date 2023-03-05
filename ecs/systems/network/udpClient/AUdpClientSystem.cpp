/*
** EPITECH PROJECT, 2023
** AUdpClientSystem
** File description:
** AUdpClientSystem
*/

#include "AUdpClientSystem.hpp"

namespace rtype {

    AUdpClientSystem::AUdpClientSystem(const std::string &libraryName) : _libraryName(libraryName)
    {
    }


    const std::string &AUdpClientSystem::getLibraryName() const
    {
        return _libraryName;
    }
}
