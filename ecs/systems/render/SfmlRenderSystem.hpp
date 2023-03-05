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
    #include "IScene.hpp"

    #include "Storage.hpp"

    #include "Sprite.hpp"
    #include "Sound.hpp"
    #include "Text.hpp"
    #include "Animation.hpp"

    namespace rtype {
        /**
         * @brief The Render System for SFML library
         * 
         */
        class SfmlRenderSystem : public ARenderSystem {
            public:
                /**
                 * @brief Construct a new Sfml Render System object with the "SFML" library name
                 * 
                 */
                SfmlRenderSystem();

                /**
                 * @brief Destroy the Sfml Render System object
                 * 
                 */
                ~SfmlRenderSystem();

                /**
                 * @brief init the SFML Render System object
                 * 
                 * @details get the singleton storage, destroy all existing rendering components than create the window
                 */
                void init();

                /**
                 * @brief display and play all components that can be rendered or played
                 * 
                 * @param scene the current scene
                 */
                void update(std::shared_ptr<IScene> &scene);

                /**
                 * @brief Destroy all Rendering Components
                 * 
                 */
                void destroy();

                /**
                 * @brief check if the game is still playing
                 * 
                 * @return true if the game is still playing, false otherwise
                 */
                bool isGameStillPlaying();

                /**
                 * @brief Get the Current Scene object
                 * 
                 * @return the current scene as a const size_t&
                 */
                const size_t &getCurrentScene() const;

            private:
                /**
                 * @brief Add or update the sprite in the texture and sprite cache for rendering it after
                 * 
                 * @param sprite the sprite that will be added or updated
                 * @param entity the entity id needed by the cache (a map) as a key
                 * @param animation the Animation ComponentMap used if the sprite as an animation
                 */
                void setSpriteComponents(const Sprite &sprite, const unsigned long &entity, const std::shared_ptr<ComponentMap<Animation>> &animation);

                /**
                 * @brief Add or update the text in the text and font cache for rendering it after
                 * 
                 * @param text the text that will be added or updated
                 * @param entity the entity id needed by the cache (a map) as a key
                 */
                void setTextComponents(const Text &text, const unsigned long &entity);

                /**
                 * @brief Add or update the sound in the music cache for playing it after
                 * 
                 * @param sound the sound that will be added or updated
                 * @param entity the entity id needed by the cache (a map) as a key
                 */
                void setSoundComponents(const Sound &sound, const unsigned long &entity);

                /**
                 * @brief this method call all the set methods
                 * 
                 * @param sprite the Sprite ComponentMap
                 * @param animation the Animation ComponentMap
                 * @param text the Text ComponentMap
                 * @param sound the Sound ComponentMap
                 */
                void updateComponents(const std::shared_ptr<ComponentMap<Sprite>> &sprite, const std::shared_ptr<ComponentMap<Animation>> &animation,
                const std::shared_ptr<ComponentMap<Text>> &text, const std::shared_ptr<ComponentMap<Sound>> &sound);

                /**
                 * @brief draw all sprites that must be drawn in the window
                 * 
                 * @param sprite the Sprite ComponentMap
                 */
                void drawSprite(const std::shared_ptr<ComponentMap<Sprite>> &sprite);

                /**
                 * @brief draw all texts that must be drawn in the window
                 * 
                 * @param text the Text ComponentMap
                 */
                void drawText(const std::shared_ptr<ComponentMap<Text>> &text);

                /**
                 * @brief play all the musics that must be played
                 * 
                 * @param sound the Sound ComponentMap
                 */
                void playMusic(const std::shared_ptr<ComponentMap<Sound>> &sound);

                /**
                 * @brief stop all the musics that must be played
                 * 
                 * @param sound the Sound ComponentMap
                 */
                void stopMusic(const std::shared_ptr<ComponentMap<Sound>> &sound)
                {
                    for (auto &music : _musicCache) {
                        if (sound->contains(music.first) == false)
                            continue;
                        if (music.second.first->getStatus() == sf::SoundSource::Playing) {
                            music.second.first->pause();
                            sound->get(music.first).setStatus(Sound::SoundStatus::PLAY);
                        }
                    }
                }

                /**
                 * @brief the singleton storage
                 * 
                 */
                std::shared_ptr<Storage> _storage;

                /**
                 * @brief the texture cache that will keep every sf::Texture with the image file path as a key
                 * 
                 */
                std::unordered_map<std::string, sf::Texture *> _textureCache;

                /**
                 * @brief the sprite cache that will keep every sf::Sprite with the entity id as a key 
                 * 
                 */
                std::map<unsigned long, sf::Sprite *> _spriteCache;

                /**
                 * @brief the font cache that will keep every sf::Font with the font file path as a key
                 * 
                 */
                std::unordered_map<std::string, sf::Font *> _fontCache;

                /**
                 * @brief the text cache that will keep every sf::Text with the entity id as a key
                 * 
                 */
                std::map<unsigned long, sf::Text *> _textCache;

                /**
                 * @brief the music cache that will keep every sf::Music and Sound status with the entity id as a key
                 * 
                 */
                std::unordered_map<unsigned long, std::pair<sf::Music *, Sound::SoundStatus>> _musicCache;
        };
    }

#endif /* !_RenderSystem_ */