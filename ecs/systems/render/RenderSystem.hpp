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

            void initRenderingComponents(const std::shared_ptr<ComponentMap<Sprite>> &sprite,  const std::shared_ptr<ComponentMap<Animation>> &animation, const std::shared_ptr<ComponentMap<Text>> &text, const std::shared_ptr<ComponentMap<Sound>> &sound);
            void displayContent(const std::shared_ptr<ComponentMap<Sprite>> &sprite, const std::shared_ptr<ComponentMap<Animation>> &animation, const std::shared_ptr<ComponentMap<Text>> &text, const std::shared_ptr<ComponentMap<Sound>> &sound);
            void destroyRenderingComponents();

        private:
            void setSpriteComponents(const Sprite &sprite, const unsigned long &entity, const std::shared_ptr<ComponentMap<Animation>> &animation);
            void setTextComponents(const Text &text, const unsigned long &entity);
            void setSoundComponents(const Sound &sound);

            void updateComponents(const std::shared_ptr<ComponentMap<Sprite>> &sprite, const std::shared_ptr<ComponentMap<Animation>> &animation, const std::shared_ptr<ComponentMap<Text>> &text, const std::shared_ptr<ComponentMap<Sound>> &sound);

            void drawSprite(const std::shared_ptr<ComponentMap<Sprite>> &sprite);
            void drawText(const std::shared_ptr<ComponentMap<Text>> &text);
            void playMusic(const std::shared_ptr<ComponentMap<Sound>> &sound);

            sf::RenderWindow _window;

            std::unordered_map<std::string, sf::Texture *> _textureCache;
            std::unordered_map<unsigned long, sf::Sprite *> _spriteCache;

            std::unordered_map<std::string, sf::Font *> _fontCache;
            std::unordered_map<unsigned long, sf::Text *> _textCache;

            std::unordered_map<std::string, std::pair<sf::Music *, Sound::SoundStatus>> _musicCache;
    };

#endif /* !_RenderSystem_ */