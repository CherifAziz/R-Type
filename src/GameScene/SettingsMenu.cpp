/*
** EPITECH PROJECT, 2023
** SettingsMenu.cpp
** File description:
** SettingsMenu.cpp
*/

#include "SettingsMenu.hpp"

namespace rtype {

    SettingsMenu::SettingsMenu()
    {
        initSprite();
        initSound();
        initText();
        initMovement();
        initAction();
        initAnimation();
        initButtons();
    }

    SettingsMenu::~SettingsMenu() {}

    void SettingsMenu::update(const int64_t &time, const size_t &windowWidth, const size_t &windowHeight, size_t &scene, size_t &previousScene)
    {
        entity_t player_id = _entityManager.getEntitiesFromFamily("player")[0]->getId();
        entity_t close_button_id = _entityManager.getEntitiesFromFamily("icon-button")[0]->getId();
        std::shared_ptr<ComponentMap<Button>> buttonMap = _componentManager.getComponents<Button>();
        Button &closeButton = buttonMap->get(close_button_id);

        if (closeButton.getLinkedScene() != previousScene)
            closeButton.setLinkedScene(previousScene);
        if (time % 2 == 0) {
            handleButtons(_componentManager.getComponents<Animation>(), _componentManager.getComponents<Text>(),_componentManager.getComponents<Sprite>(),
                _componentManager.getComponents<Button>(), _componentManager.getComponents<Action>()->get(player_id),
                windowWidth, windowHeight, scene);
        }
    }

    void SettingsMenu::initSprite() {
        ComponentMap<Sprite> sprite;
        Sprite background_sprite("assets/Menu-background.png", 0, 0);
        Sprite settings_background_sprite("assets/settings-bg.png", 80, 10, 1.5);
        Sprite close_button_icon_sprite("assets/cross-icon.png", 1330, 75);
        Sprite close_button_background_sprite("assets/small-button-bg.png", 1315, 60);

        sprite.put(background_sprite, _entityManager.spawnEntity("background")->getId());
        sprite.put(settings_background_sprite, _entityManager.spawnEntity("settings-background")->getId());
        sprite.put(close_button_background_sprite, _entityManager.spawnEntity("icon-button")->getId());
        sprite.put(close_button_icon_sprite, _entityManager.spawnEntity("icon")->getId());
        _componentManager.registerComponent<Sprite>(sprite);
    }

    void SettingsMenu::initSound() {
        ComponentMap<Sound> sound;
        Sound music("assets/music.ogg", true, Sound::SoundStatus::PLAY);
        Sound pow("assets/pow.ogg", false, Sound::SoundStatus::STOP);

        sound.put(music, _entityManager.spawnEntity("music")->getId());
        _componentManager.registerComponent<Sound>(sound);
    }

    void SettingsMenu::initText() {
        ComponentMap<Text> text;
        Text title("SETTINGS", "assets/font.ttf", 625, 20, 40, 1, Text::rgb_t(255, 255, 255));

        text.put(title, _entityManager.getEntitiesFromFamily("settings-background")[0]->getId());
        _componentManager.registerComponent<Text>(text);
    }

    void SettingsMenu::initMovement()
    {
        ComponentMap<Movement> movement;

        _componentManager.registerComponent<Movement>(movement);
    }

    void SettingsMenu::initAction()
    {
        ComponentMap<Action> action;
        Action player_action;

        action.put(player_action, _entityManager.spawnEntity("player")->getId());
        _componentManager.registerComponent<Action>(action);
    }

    void SettingsMenu::initAnimation()
    {
        ComponentMap<Animation> animation;
        Animation close_button_animation(85, 84, 0, 0, 1, 3, 0, 8, 100);
        Animation close_button_icon_animation(46, 39, 0, 0, 1, 3, 0, 3, 100);

        animation.put(close_button_animation, _entityManager.getEntitiesFromFamily("icon-button")[0]->getId());
        animation.put(close_button_icon_animation, _entityManager.getEntitiesFromFamily("icon")[0]->getId());
        _componentManager.registerComponent<Animation>(animation);
    }

    void SettingsMenu::initButtons()
    {
        ComponentMap<Button> button;
        Button close_button(0);

        button.put(close_button, _entityManager.getEntitiesFromFamily("icon-button")[0]->getId());
        _componentManager.registerComponent<Button>(button);
    }
}