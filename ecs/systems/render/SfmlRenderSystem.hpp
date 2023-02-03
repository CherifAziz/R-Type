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
                SfmlRenderSystem() : ARenderSystem("SFML") {}

                /**
                 * @brief Destroy the Sfml Render System object
                 * 
                 */
                ~SfmlRenderSystem() = default;

                /**
                 * @brief init the SFML Render System object
                 * 
                 * @details get the singleton storage, destroy all existing rendering components than create the window
                 */
                void init()
                {
                    _storage = Storage::getStorage();
                    destroyRenderingComponents();
                    _storage->getRenderWindow().create({1920, 1080}, "R-Type");
                }

                /**
                 * @brief display and play all components that can be rendered or played
                 * 
                 * @param sprite the Sprite ComponentMap
                 * @param animation the Animation ComponentMap
                 * @param text the Text ComponentMap
                 * @param sound the Sound ComponentMap
                 */
                void displayContent(const std::shared_ptr<ComponentMap<Sprite>> &sprite, const std::shared_ptr<ComponentMap<Animation>> &animation,
                const std::shared_ptr<ComponentMap<Text>> &text, const std::shared_ptr<ComponentMap<Sound>> &sound)
                {
                    _storage->getRenderWindow().clear();
                    if (_storage->getRenderWindow().isOpen()) {
                        updateComponents(sprite, animation, text, sound);
                        drawSprite(sprite);
                        drawText(text);
                        playMusic(sound);
                    }
                    _storage->getRenderWindow().display();
                }

                /**
                 * @brief Destroy all Rendering Components
                 * 
                 */
                void destroyRenderingComponents()
                {
                    for (auto &texture : _textureCache)
                        if (texture.second != nullptr)
                            delete texture.second;
                    for (auto &sprite : _spriteCache)
                        if (sprite.second != nullptr)
                            delete sprite.second;
                    for (auto &font : _fontCache)
                        if (font.second != nullptr)
                            delete font.second;
                    for (auto &text : _textCache)
                        if (text.second != nullptr)
                            delete text.second;
                    for (auto &music : _musicCache)
                        if (music.second.first != nullptr)
                            delete music.second.first;
                    _textureCache.clear();
                    _spriteCache.clear();
                    _fontCache.clear();
                    _textCache.clear();
                    _musicCache.clear();
                    if (_storage->getRenderWindow().isOpen())
                        _storage->getRenderWindow().close();
                }

                /**
                 * @brief Check if the window is still open
                 * 
                 * @return true if the window is still open, false otherwise
                 */
                bool isOpen() const
                {
                    return _storage->getRenderWindow().isOpen();
                }

            private:
                /**
                 * @brief Add or update the sprite in the texture and sprite cache for rendering it after
                 * 
                 * @param sprite the sprite that will be added or updated
                 * @param entity the entity id needed by the cache (a map) as a key
                 * @param animation the Animation ComponentMap used if the sprite as an animation
                 */
                void setSpriteComponents(const Sprite &sprite, const unsigned long &entity, const std::shared_ptr<ComponentMap<Animation>> &animation)
                {
                    sf::Texture *texture = NULL;
                    sf::Sprite *spr = NULL;

                    if (_textureCache.count(sprite.getFilename()) > 0)
                        texture = _textureCache[sprite.getFilename()];
                    else {
                        texture = new sf::Texture();
                        if (!texture->loadFromFile(sprite.getFilename()))
                            throw std::runtime_error("Sprite picture file not found !");
                    }

                    if (_spriteCache.count(entity) > 0)
                        spr = _spriteCache[entity];
                    else {
                        spr = new sf::Sprite();
                        spr->setTexture(*texture);
                    }

                    if (animation && animation->contains(entity) == true) {
                        Animation anim = animation->get(entity);

                        spr->setTextureRect({(int)anim.getX(), (int)anim.getY(), (int)anim.getRectWidth(), (int)anim.getRectHeight()});
                    }

                    spr->setPosition(sprite.getX(), sprite.getY());
                    spr->setScale(sprite.getScale(), sprite.getScale());

                    if (_textureCache.count(sprite.getFilename()) == 0)
                        _textureCache[sprite.getFilename()] = texture;
                    if (_spriteCache.count(entity) == 0)
                        _spriteCache[entity] = spr;
                }

                /**
                 * @brief Add or update the text in the text and font cache for rendering it after
                 * 
                 * @param text the text that will be added or updated
                 * @param entity the entity id needed by the cache (a map) as a key
                 */
                void setTextComponents(const Text &text, const unsigned long &entity)
                {
                    Text::rgb_t color = text.getColor();
                    sf::Font *font = NULL;
                    sf::Text *txt = NULL;

                    if (_fontCache.count(text.getFont()) > 0)
                        font = _fontCache[text.getFont()];
                    else {
                        font = new sf::Font();
                        if (!font->loadFromFile(text.getFont()))
                            throw std::runtime_error("Font file not found !");
                    }

                    if (_textCache.count(entity) > 0)
                        txt = _textCache[entity];
                    else {
                        txt = new sf::Text();
                        txt->setFont(*font);
                    }

                    txt->setString(text.getText());
                    txt->setFillColor(sf::Color(color.r, color.g, color.b));
                    txt->setPosition(text.getX(), text.getY());
                    txt->setScale(text.getScale(), text.getScale());
                    txt->setCharacterSize(text.getCharacterSize());

                    if (_fontCache.count(text.getFont()) == 0)
                        _fontCache[text.getFont()] = font;
                    if (_textCache.count(entity) == 0)
                        _textCache[entity] = txt;
                }

                /**
                 * @brief Add or update the sound in the music cache for playing it after
                 * 
                 * @param sound the sound that will be added or updated
                 * @param entity the entity id needed by the cache (a map) as a key
                 */
                void setSoundComponents(const Sound &sound, const unsigned long &entity)
                {
                    sf::Music *music = NULL;

                    if (_musicCache.count(entity) > 0)
                        music = _musicCache[entity].first;
                    else {
                        music = new sf::Music();
                        if (!music->openFromFile(sound.getFile()))
                            throw std::runtime_error("Music file not found !");
                    }
                    music->setLoop(sound.isLooping());
                    if (_musicCache.count(entity) == 0)
                        _musicCache[entity] = std::make_pair(music, sound.getStatus());
                    else
                        _musicCache[entity].second = sound.getStatus();
                }

                /**
                 * @brief this method call all the set methods
                 * 
                 * @param sprite the Sprite ComponentMap
                 * @param animation the Animation ComponentMap
                 * @param text the Text ComponentMap
                 * @param sound the Sound ComponentMap
                 */
                void updateComponents(const std::shared_ptr<ComponentMap<Sprite>> &sprite, const std::shared_ptr<ComponentMap<Animation>> &animation,
                const std::shared_ptr<ComponentMap<Text>> &text, const std::shared_ptr<ComponentMap<Sound>> &sound)
                {
                    for (uint32_t it = 0; it < sprite->getSize(); it++)
                        setSpriteComponents(sprite->getFromIndex(it), sprite->getEntityId(sprite->getFromIndex(it)), animation);
                    for (uint32_t it = 0; it < text->getSize(); it++)
                        setTextComponents(text->getFromIndex(it), text->getEntityId(text->getFromIndex(it)));
                    for (uint32_t it = 0; it < sound->getSize(); it++)
                        setSoundComponents(sound->getFromIndex(it), sound->getEntityId(sound->getFromIndex(it)));
                }

                /**
                 * @brief draw all sprites that must be drawn in the window
                 * 
                 * @param sprite the Sprite ComponentMap
                 */
                void drawSprite(const std::shared_ptr<ComponentMap<Sprite>> &sprite)
                {
                    for (auto &spr : _spriteCache) {
                        if (sprite->contains(spr.first))
                            _storage->getRenderWindow().draw(*spr.second);
                    }
                }

                /**
                 * @brief draw all texts that must be drawn in the window
                 * 
                 * @param text the Text ComponentMap
                 */
                void drawText(const std::shared_ptr<ComponentMap<Text>> &text)
                {
                    for (auto &txt : _textCache) {
                        if (text->contains(txt.first))
                            _storage->getRenderWindow().draw(*txt.second);
                    }
                }

                /**
                 * @brief play all the musics that must be played
                 * 
                 * @param sound the Sound ComponentMap
                 */
                void playMusic(const std::shared_ptr<ComponentMap<Sound>> &sound)
                {
                    for (auto &music : _musicCache) {
                        if (sound->contains(music.first) == false)
                            continue;
                        if (music.second.second == Sound::SoundStatus::PLAY) {
                            if (music.second.first->getStatus() != sf::SoundSource::Playing)
                                music.second.first->play();
                            sound->get(music.first).setStatus(Sound::SoundStatus::PLAYING);
                        } else if (music.second.second == Sound::SoundStatus::PAUSE)
                            music.second.first->pause();
                        else if (music.second.second == Sound::SoundStatus::STOP)
                            music.second.first->stop();
                        else if (music.second.first->getStatus() != sf::SoundSource::Playing && music.second.first->getLoop() == false) {
                            music.second.first->stop();
                            sound->get(music.first).setStatus(Sound::SoundStatus::STOP);
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
                std::unordered_map<unsigned long, sf::Sprite *> _spriteCache;

                /**
                 * @brief the font cache that will keep every sf::Font with the font file path as a key
                 * 
                 */
                std::unordered_map<std::string, sf::Font *> _fontCache;

                /**
                 * @brief the text cache that will keep every sf::Text with the entity id as a key
                 * 
                 */
                std::unordered_map<unsigned long, sf::Text *> _textCache;

                /**
                 * @brief the music cache that will keep every sf::Music and Sound status with the entity id as a key
                 * 
                 */
                std::unordered_map<unsigned long, std::pair<sf::Music *, Sound::SoundStatus>> _musicCache;
        };
    }

#endif /* !_RenderSystem_ */