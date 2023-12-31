/*
** EPITECH PROJECT, 2023
** RenderSystem
** File description:
** RenderSystem
*/

#include "SfmlRenderSystem.hpp"

namespace rtype {

    SfmlRenderSystem::SfmlRenderSystem() : ARenderSystem("SFML")
    {
    }

    SfmlRenderSystem::~SfmlRenderSystem()
    {
        if (_storage->getRenderWindow().isOpen())
            _storage->getRenderWindow().close();
    }

    void SfmlRenderSystem::init()
    {
        _storage = Storage::getStorage();
        for (auto &sprite : _spriteCache)
            if (sprite.second != nullptr)
                delete sprite.second;
        _spriteCache.clear();
        for (auto &text : _textCache)
            if (text.second != nullptr)
                delete text.second;
        _textCache.clear();
        if (!_storage->getRenderWindow().isOpen())
            _storage->getRenderWindow().create({1440, 810}, "R-Type");
        _storage->getRenderWindow().setFramerateLimit(60);
    }

    void SfmlRenderSystem::update(std::shared_ptr<IScene> &scene)
    {
        std::shared_ptr<ComponentMap<Sprite>> sprite = scene->getComponentManager().getComponents<Sprite>();
        std::shared_ptr<ComponentMap<Animation>> animation = scene->getComponentManager().getComponents<Animation>();
        std::shared_ptr<ComponentMap<Text>> text = scene->getComponentManager().getComponents<Text>();
        std::shared_ptr<ComponentMap<Sound>> sound = scene->getComponentManager().getComponents<Sound>();

        _storage->getRenderWindow().clear();
        if (_storage->getRenderWindow().isOpen()) {
            updateComponents(sprite, animation, text, sound);
            drawSprite(sprite);
            drawText(text);
            if (_storage->getSoundState() == true)
                playMusic(sound);
            else
                stopMusic(sound);
        }
        _storage->getRenderWindow().display();
    }

    void SfmlRenderSystem::destroy()
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
    }

    bool SfmlRenderSystem::isGameStillPlaying()
    {
        return _storage->getRenderWindow().isOpen() && _storage->isStillPlaying();
    }

    const size_t &SfmlRenderSystem::getCurrentScene() const
    {
        return _storage->getCurrentScene();
    }

    void SfmlRenderSystem::setSpriteComponents(const Sprite &sprite, const unsigned long &entity, const std::shared_ptr<ComponentMap<Animation>> &animation)
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

    void SfmlRenderSystem::setTextComponents(const Text &text, const unsigned long &entity)
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

    void SfmlRenderSystem::setSoundComponents(const Sound &sound, const unsigned long &entity)
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

    void SfmlRenderSystem::updateComponents(const std::shared_ptr<ComponentMap<Sprite>> &sprite, const std::shared_ptr<ComponentMap<Animation>> &animation,
                const std::shared_ptr<ComponentMap<Text>> &text, const std::shared_ptr<ComponentMap<Sound>> &sound)
    {
        for (uint32_t it = 0; it < sprite->getSize(); it++) {
            setSpriteComponents(sprite->getFromIndex(it), sprite->getEntityId(sprite->getFromIndex(it)), animation);
        } for (uint32_t it = 0; it < text->getSize(); it++) {
            setTextComponents(text->getFromIndex(it), text->getEntityId(text->getFromIndex(it)));
        } for (uint32_t it = 0; it < sound->getSize(); it++) {
            setSoundComponents(sound->getFromIndex(it), sound->getEntityId(sound->getFromIndex(it)));
        }
    }

    void SfmlRenderSystem::drawSprite(const std::shared_ptr<ComponentMap<Sprite>> &sprite)
    {
        for (auto &spr : _spriteCache) {
            if (sprite->contains(spr.first))
                _storage->getRenderWindow().draw(*spr.second);
        }
    }

    void SfmlRenderSystem::drawText(const std::shared_ptr<ComponentMap<Text>> &text)
    {
        for (auto &txt : _textCache) {
            if (text->contains(txt.first))
                _storage->getRenderWindow().draw(*txt.second);
        }
    }

    void SfmlRenderSystem::playMusic(const std::shared_ptr<ComponentMap<Sound>> &sound)
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

}