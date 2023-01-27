/*
** EPITECH PROJECT, 2023
** ARenderSystem
** File description:
** ARenderSystem
*/

#ifndef _ARenderSystem_
    #define _ARenderSystem_

    #include "IRenderSystem.hpp"

    class ARenderSystem : public IRenderSystem {
        public:
            ARenderSystem(const std::string &libraryName) : _libraryName(libraryName) {}

            const std::string &getLibraryName() const
            {
                return _libraryName;
            }
        protected:
            std::string _libraryName;
    };

#endif /* !_ARenderSystem_ */