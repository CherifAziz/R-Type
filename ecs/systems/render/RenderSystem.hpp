/*
** EPITECH PROJECT, 2023
** RenderSystem
** File description:
** RenderSystem
*/

#ifndef _RenderSystem_
    #define _RenderSystem_

    #include <SFML/Graphics.hpp>
    #include <SFML/Audio.hpp>

    #include <unordered_map>
    #include <memory>

    #include "ARenderSystem.hpp"
    #include "Entity.hpp"

    class RenderSystem : public ARenderSystem {
        public:
            RenderSystem();
            ~RenderSystem();

            void init_rendering_components(const ComponentMap<Render> &render);
            void display_content(const ComponentMap<Render> &render);
            void destroy_rendering_components();
        private:
            std::unordered_map<std::string, sf::Texture *> _textureCache;
            std::unordered_map<std::shared_ptr<Entity>, sf::Sprite *> _spriteCache;

            // std::unordered_map<std::string, sf::Font *> _fontCache;
            // std::unordered_map<std::shared_ptr<Entity>, sf::Text *> _textCache;

            // std::unordered_map<std::string, sf::Music *> _musicCache;
    };

#endif /* !_RenderSystem_ */