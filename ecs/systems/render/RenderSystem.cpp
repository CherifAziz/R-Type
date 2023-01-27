/*
** EPITECH PROJECT, 2023
** RenderSystem
** File description:
** RenderSystem
*/

#include "RenderSystem.hpp"

RenderSystem::RenderSystem()
{

}

RenderSystem::~RenderSystem()
{

}

void RenderSystem::init()
{
    destroyRenderingComponents();
    _window.create({1920, 1080}, "R-Type");
}

void RenderSystem::displayContent(const std::shared_ptr<ComponentMap<Sprite>> &sprite, const std::shared_ptr<ComponentMap<Animation>> &animation,
const std::shared_ptr<ComponentMap<Text>> &text, const std::shared_ptr<ComponentMap<Sound>> &sound)
{
    _window.clear();
    if (_window.isOpen()) {
        updateComponents(sprite, animation, text, sound);
        drawSprite(sprite);
        drawText(text);
        playMusic(sound);
    }
    _window.display();
}

void RenderSystem::destroyRenderingComponents()
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
    if (_window.isOpen())
        _window.close();
}

const bool &RenderSystem::isOpen() const
{
    return _window.isOpen();
}

void RenderSystem::setSpriteComponents(const Sprite &sprite, const unsigned long &entity, const std::shared_ptr<ComponentMap<Animation>> &animation)
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

    if (animation->contains(entity) == true) {
        Animation anim = animation->get(entity);

        texture->setTextureRect((sf::IntRect){anim.getX(), anim.getY(), anim.getRectWidth(), anim.getRectHeight()});
    }

    if (_spriteCache.count(entity) > 0)
        spr = _spriteCache[entity];
    else {
        spr = new sf::Sprite();
        spr->setTexture(texture);
    }

    spr->setPosition(sprite.getX(), sprite.getY());
    spr->setScale(sprite.getScale(), sprite.getScale());

    if (_textureCache.count(sprite.getFilename()) == 0)
        _textureCache[sprite.getFilename()] = texture;
    if (_spriteCache.count(entity) == 0)
        _spriteCache[entity] = spr;
}

void RenderSystem::setTextComponents(const Text &text, const unsigned long &entity)
{
    rbt_t color = text.get_color();
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
        txt->setFont(text.getFont());
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

void RenderSystem::setSoundComponents(const Sound &sound)
{
    sf::Music *music = NULL;

    if (_musicCache.count(sound.getFile()) > 0)
        music = _musicCache[sound.getFile()].first;
    else {
        music = new sf::Music();
        if (!music->openFromFile(sound.getFile()))
            throw std::runtime_error("Music file not found !");
    }
    music->setLoop(sound.isLooping());
    if (_musicCache.count(sound.getFile()) == 0)
        _musicCache[sound.getFile()] = std::make_pair(music, sound.getStatus());
    else
        _musicCache[sound.getFile()].second = sound.getStatus();
}

void RenderSystem::updateComponents(const std::shared_ptr<ComponentMap<Sprite>> &sprite, const std::shared_ptr<ComponentMap<Animation>> &animation,
const std::shared_ptr<ComponentMap<Text>> &text, const std::shared_ptr<ComponentMap<Sound>> &sound)
{
    for (int32_t it = 0; it < sprite->getSize(); it++) {
        if (sprite->contains(it))
            setSpriteComponents(sprite->get(it), animation);
    }
    for (int32_t it = 0; it < text->getSize(); it++) {
        if (text->contains(it))
            setTextComponents(text->get(it));
    }
    for (int32_t it = 0; it < sound->getSize(); it++) {
        if (sound->contains(it))
            setSoundComponents(sound->get(it));
    }
}

void RenderSystem::drawSprite(const std::shared_ptr<ComponentMap<Sprite>> &sprite)
{
    for (auto &spr : _spriteCache) {
        if (sprite->contains(spr.first))
            _window.draw(spr.second);
    }
}

void RenderSystem::drawText(const std::shared_ptr<ComponentMap<Text>> &text)
{
    for (auto &txt : _textCache) {
        if (text->contains(txt.first))
            _window.draw(txt.second);
    }
}

void RenderSystem::playMusic(const std::shared_ptr<ComponentMap<Sound>> &sound)
{
    for (auto &music : _musicCache) {
        if (music.second.second == Sound::SoundStatus::PLAY) {
            if (music.second.first->getStatus() != sf::SoundSource::Playing)
                music.second.first->play();
            music.second.second = Sound::SoundStatus::PAUSE;
        } else if (music.second.second == Sound::SoundStatus::PAUSE)
            music.second.first->pause();
        else
            music.second.first->stop();
    }
}
