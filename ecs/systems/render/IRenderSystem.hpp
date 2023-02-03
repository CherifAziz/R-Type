/*
** EPITECH PROJECT, 2023
** IRenderSystem
** File description:
** IRenderSystem
*/

#ifndef _IRenderSystem
    #define _IRenderSystem_

    #include <string.h>

    namespace rtype {
        class IRenderSystem {
            public:
                virtual ~IRenderSystem() = default;

                virtual void init() = 0;
                virtual const std::string &getLibraryName() const = 0;
                virtual void destroyRenderingComponents() = 0;
        };
    }

#endif /* !_IRenderSystem */