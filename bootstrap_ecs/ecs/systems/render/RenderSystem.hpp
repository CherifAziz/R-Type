/*
** EPITECH PROJECT, 2023
** RenderSystem
** File description:
** RenderSystem
*/

#ifndef _RenderSystem_
    #define _RenderSystem_

    #include "ARenderSystem.hpp"

    class RenderSystem : public ARenderSystem {
        public:
            RenderSystem();
            ~RenderSystem();

            void init_rendering_components(const ComponentMap<Render> &render);
            void display_content(const ComponentMap<Render> &render);
            void destroy_rendering_components();
        private:

    };

#endif /* !_RenderSystem_ */