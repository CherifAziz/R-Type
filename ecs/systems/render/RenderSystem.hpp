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

    #include "Sprite.hpp"
    #include "Sound.hpp"
    #include "Text.hpp"
    #include "Animation.hpp"

    class RenderSystem : public ARenderSystem {
        public:
            RenderSystem();
            ~RenderSystem();

            void init_rendering_components(const std::shared_ptr<ComponentMap<Sprite>> &sprite,  const std::shared_ptr<ComponentMap<Animation>> &animation, const std::shared_ptr<ComponentMap<Text>> &text, const std::shared_ptr<ComponentMap<Sound>> &sound);
            void display_content(const std::shared_ptr<ComponentMap<Sprite>> &sprite, const std::shared_ptr<ComponentMap<Animation>> &animation, const std::shared_ptr<ComponentMap<Text>> &text, const std::shared_ptr<ComponentMap<Sound>> &sound);
            void destroy_rendering_components();

        private:
            void set_sprite_components(const Sprite &sprite, const unsigned long &entity, const std::shared_ptr<ComponentMap<Animation>> &animation);
            void set_text_components(const Text &text, const unsigned long &entity);
            void set_sound_components(const Sound &sound);

            std::unordered_map<std::string, sf::Texture *> _textureCache;
            std::unordered_map<unsigned long, sf::Sprite *> _spriteCache;

            std::unordered_map<std::string, sf::Font *> _fontCache;
            std::unordered_map<unsigned long, sf::Text *> _textCache;

            std::unordered_map<std::string, sf::Music *> _musicCache;
    };

#endif /* !_RenderSystem_ */