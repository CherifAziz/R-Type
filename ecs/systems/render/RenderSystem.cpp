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

void RenderSystem::init_rendering_components(const std::shared_ptr<ComponentMap<Sprite>> &sprite, const std::shared_ptr<ComponentMap<Animation>> &animation,
const std::shared_ptr<ComponentMap<Text>> &text, const std::shared_ptr<ComponentMap<Sound>> &sound)
{
    for (int32_t it = 0; it < sprite->get_size(); it++) {
        if (sprite->contains(it) == false)
            continue;
        set_sprite_components(sprite->get(it), animation);
    }
    for (int32_t it = 0; it < text->get_size(); it++) {
        if (text->contains(it) == false)
            continue;
        set_text_components(text->get(it));
    }
    for (int32_t it = 0; it < sound->get_size(); it++) {
        if (sound->contains(it) == false)
            continue;
        set_sound_components(sound->get(it));
    }
}

void RenderSystem::display_content(const std::shared_ptr<ComponentMap<Sprite>> &sprite, const std::shared_ptr<ComponentMap<Animation>> &animation,
const std::shared_ptr<ComponentMap<Text>> &text, const std::shared_ptr<ComponentMap<Sound>> &sound)
{

}

void RenderSystem::destroy_rendering_components()
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
}

void RenderSystem::set_sprite_components(const Sprite &sprite, const unsigned long &entity, const std::shared_ptr<ComponentMap<Animation>> &animation)
{
    sf::Texture *texture = new sf::Texture();
    sf::Sprite *spr = new sf::Sprite();

    if (!texture->loadFromFile(sprite.getFilename()))
        throw std::runtime_error("Sprite picture file not found !");
    if (animation->contains(entity) == true) {
        Animation anim = animation->get(entity);

        texture->setTextureRect((sf::IntRect){anim.getX(), anim.getY(), anim.getRectWidth(), anim.getRectHeight()});
    }
    _textureCache[sprite.getFilename()] = texture;
    spr->setTexture(texture);
    spr->setPosition(sprite.getX(), sprite.getY());
    spr->setScale(sprite.getScale(), sprite.getScale());
    _spriteCache[entity] = sprite;
}

void RenderSystem::set_text_components(const Text &text, const unsigned long &entity)
{
    rbt_t color = text.get_color();
    sf::Font *font = new sf::Font();

    if (!font->loadFromFile(text.getFont()))
        throw std::runtime_error("Font file not found !");
    _fontCache[text.getFont()] = font;
    _fontCache.push_back(font);

    sf::Text *txt = new sf::Text(text.getText(), text.getFont(), text.getCharacterSize());
    txt->setFillColor(sf::Color(color.r, color.g, color.b));
    txt->setPosition(text.getX(), text.getY());
    txt->setScale(text.getScale(), text.getScale());
    txt->setCharacterSize(text.getCharacterSize());
    _textCache[entity] = txt;
}

void RenderSystem::set_sound_components(const Sound &sound)
{
    sf::Music *music = new sf::Music();

    if (!music->openFromFile(sound.getFile()))
        throw std::runtime_error("Music file not found !");
    music->setLoop(sound.isLooping());
    _musicCache[sound.getFile()] = music;
}