/*
** EPITECH PROJECT, 2023
** AInputSystem
** File description:
** AInputSystem
*/

#ifndef _AInputSystem_
    #define _AInputSystem_

    #include "IInputSystem.hpp"

    class AInputSystem : public IInputSystem {
        public:
            AInputSystem(const std::string &libraryName) : _libraryName(libraryName) {}

            const std::string &getLibraryName() const
            {
                return _libraryName;
            }

        protected:
            std::string _libraryName;
    };

#endif /* !_AInputSystem_ */