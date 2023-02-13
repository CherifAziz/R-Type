/*
** EPITECH PROJECT, 2023
** HomeMenuScene.cpp
** File description:
** HomeMenuScene.cpp
*/

#include "HomeMenuScene.hpp"

namespace rtype {

    HomeMenuScene::HomeMenuScene() {}

    HomeMenuScene::~HomeMenuScene() {}

    void HomeMenuScene::update(const int64_t &time)
    {
        entity_t player_id = _entityManager.getEntitiesFromFamily("player")[0]->getId();

        if (time % 2 == 0) {
            handleButtons(_componentManager.getComponents<Animation>(), _componentManager.getComponents<Sprite>(),
                _componentManager.getComponents<Action>()->get(player_id));
        }
    }

    void HomeMenuScene::destroy()
    {
    }

    const bool &HomeMenuScene::isGameStillPlaying() const
    {
        return _entityManager.isGamePlaying();
    }

    void HomeMenuScene::initSprite() {
        ComponentMap<Sprite> sprite;
        Sprite background_sprite("assets/Menu-background.png", 0, 0);
        Sprite button_background_sprite("assets/Button-bg.png", 340, 317.5);

        sprite.put(background_sprite, _entityManager.spawnEntity("background")->getId());
        sprite.put(button_background_sprite, _entityManager.spawnEntity("button")->getId());
        _componentManager.registerComponent<Sprite>(sprite);
    }

    void HomeMenuScene::initSound() {
        ComponentMap<Sound> sound;
        Sound music("assets/music.ogg", true, Sound::SoundStatus::PLAY);
        Sound pow("assets/pow.ogg", false, Sound::SoundStatus::STOP);

        sound.put(music, _entityManager.spawnEntity("music")->getId());
        _componentManager.registerComponent<Sound>(sound);
    }

    void HomeMenuScene::initText() {
        ComponentMap<Text> text;
        Text title("START", "assets/font.ttf", 470, 305, 60, 1, Text::rgb_t(0, 0, 0));

        text.put(title, _entityManager.getEntitiesFromFamily("button")[0]->getId());
        _componentManager.registerComponent<Text>(text);
    }

    void HomeMenuScene::initMovement()
    {
        ComponentMap<Movement> movement;

        _componentManager.registerComponent<Movement>(movement);
    }

    void HomeMenuScene::initAction()
    {
        ComponentMap<Action> action;
        Action player_action;

        action.put(player_action, _entityManager.spawnEntity("player")->getId());
        _componentManager.registerComponent<Action>(action);
    }

    void HomeMenuScene::initAnimation()
    {
        ComponentMap<Animation> animation;
        Animation start_button_animation(465, 75, 0, 0, 1, 1, 0, 0, 0);

        animation.put(start_button_animation, _entityManager.getEntitiesFromFamily("button")[0]->getId());
        _componentManager.registerComponent<Animation>(animation);
    }
}