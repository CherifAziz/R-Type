/*
** EPITECH PROJECT, 2023
** IRenderSystem
** File description:
** IRenderSystem
*/

#ifndef _IRenderSystem
    #define _IRenderSystem_

    #include <string.h>

    #include "ComponentMap.hpp"
    #include "Render.hpp"

    class IRenderSystem {
        public:
            virtual ~IRenderSystem() = default;

            virtual const std::string &getLibraryName() const = 0;

            virtual void init_rendering_components(const ComponentMap<Render> &render) = 0;
            virtual void display_content(const ComponentMap<Render> &render) = 0;
            virtual void destroy_rendering_components() = 0;
    };

#endif /* !_IRenderSystem */