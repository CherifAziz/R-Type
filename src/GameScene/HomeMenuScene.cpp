/*
** EPITECH PROJECT, 2023
** HomeMenuScene.cpp
** File description:
** HomeMenuScene.cpp
*/

#include "HomeMenuScene.hpp"

namespace rtype {

    HomeMenuScene::HomeMenuScene()
    {
        initSprite();
        initSound();
        initText();
        initMovement();
        initAction();
        initAnimation();
        initButtons();
    }

    HomeMenuScene::~HomeMenuScene() {}

    void HomeMenuScene::update(const int64_t &time, const size_t &windowWidth, const size_t &windowHeight, size_t &scene, size_t &/*previousScene*/, bool &/*soundState*/)
    {
        entity_t player_id = _entityManager.getEntitiesFromFamily("player")[0]->getId();

        if (time % 2 == 0) {
            handleButtons(_componentManager.getComponents<Animation>(), _componentManager.getComponents<Text>(), _componentManager.getComponents<Sprite>(),
                _componentManager.getComponents<Button>(), _componentManager.getComponents<Action>()->get(player_id),
                windowWidth, windowHeight, scene);
        }
    }

    void HomeMenuScene::initSprite() {
        ComponentMap<Sprite> sprite;
        Sprite background_sprite("assets/Menu-background.png", 0, 0);
        Sprite play_button_background_sprite("assets/Button-bg.png", 300, 250);
        Sprite online_button_background_sprite("assets/Button-bg.png", 300, 360);
        Sprite exit_button_background_sprite("assets/Button-bg.png", 300, 470);
        Sprite settings_button_background_sprite("assets/small-button-bg.png", 1345, 35);
        Sprite settings_icon_sprite("assets/settings-icon.png", 1360, 50);

        sprite.put(background_sprite, _entityManager.spawnEntity("background")->getId());
        sprite.put(play_button_background_sprite, _entityManager.spawnEntity("text-button")->getId());
        sprite.put(online_button_background_sprite, _entityManager.spawnEntity("text-button")->getId());
        sprite.put(exit_button_background_sprite, _entityManager.spawnEntity("text-button")->getId());
        sprite.put(settings_button_background_sprite, _entityManager.spawnEntity("icon-button")->getId());
        sprite.put(settings_icon_sprite, _entityManager.spawnEntity("icon")->getId());
        _componentManager.registerComponent<Sprite>(sprite);
    }

    void HomeMenuScene::initSound() {
        ComponentMap<Sound> sound;
        Sound music("assets/music.ogg", true, Sound::SoundStatus::PLAY);

        sound.put(music, _entityManager.spawnEntity("music")->getId());
        _componentManager.registerComponent<Sound>(sound);
    }

    void HomeMenuScene::initText() {
        ComponentMap<Text> text;
        Text play_button_title("PLAY", "assets/font.ttf", 390, 257.5, 45, 1, Text::rgb_t(255, 255, 255));
        Text online_button_title("ONLINE", "assets/font.ttf", 365, 367.5, 45, 1, Text::rgb_t(255, 255, 255));
        Text exit_button_title("EXIT", "assets/font.ttf", 400, 477.5, 45, 1, Text::rgb_t(255, 255, 255));

        text.put(play_button_title, _entityManager.getEntitiesFromFamily("text-button")[0]->getId());
        text.put(online_button_title, _entityManager.getEntitiesFromFamily("text-button")[1]->getId());
        text.put(exit_button_title, _entityManager.getEntitiesFromFamily("text-button")[2]->getId());
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
        Animation text_button_animation(380, 98, 0, 0, 1, 3, 0, 7, 100);
        Animation icon_button_animation(85, 84, 0, 0, 1, 3, 0, 8, 100);
        Animation settings_icon_animation(46, 39, 0, 0, 1, 3, 0, 3, 100);

        animation.put(text_button_animation, _entityManager.getEntitiesFromFamily("text-button")[0]->getId());
        animation.put(text_button_animation, _entityManager.getEntitiesFromFamily("text-button")[1]->getId());
        animation.put(text_button_animation, _entityManager.getEntitiesFromFamily("text-button")[2]->getId());
        animation.put(icon_button_animation, _entityManager.getEntitiesFromFamily("icon-button")[0]->getId());
        animation.put(settings_icon_animation, _entityManager.getEntitiesFromFamily("icon")[0]->getId());
        _componentManager.registerComponent<Animation>(animation);
    }

    void HomeMenuScene::initButtons()
    {
        ComponentMap<Button> button;
        Button start_button(2);
        Button settings_button(1);
        Button online_button(2);
        Button exit_button(-1);

        button.put(start_button, _entityManager.getEntitiesFromFamily("text-button")[0]->getId());
        button.put(online_button, _entityManager.getEntitiesFromFamily("text-button")[1]->getId());
        button.put(exit_button, _entityManager.getEntitiesFromFamily("text-button")[2]->getId());
        button.put(settings_button, _entityManager.getEntitiesFromFamily("icon-button")[0]->getId());
        _componentManager.registerComponent<Button>(button);
    }
}