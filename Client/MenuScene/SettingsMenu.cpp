/*
** EPITECH PROJECT, 2023
** SettingsMenu.cpp
** File description:
** SettingsMenu.cpp
*/

#include "config.hpp"
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

    void SettingsMenu::update(const int64_t &time, const size_t &windowWidth, const size_t &windowHeight, size_t &scene, size_t &previousScene, bool &soundState)
    {
        entity_t player_id = _entityManager.getEntitiesFromFamily("player")[0]->getId();
        entity_t close_button_id = _entityManager.getEntitiesFromFamily("icon-button")[0]->getId();
        std::shared_ptr<ComponentMap<Button>> buttonMap = _componentManager.getComponents<Button>();
        Button &closeButton = buttonMap->get(close_button_id);

        if (closeButton.getLinkedScene() != previousScene)
            closeButton.setLinkedScene(previousScene);
        if (time % 2 == 0) {
            handleButtons(_componentManager.getComponents<Animation>(), _componentManager.getComponents<Text>(), _componentManager.getComponents<Sprite>(),
                _componentManager.getComponents<Button>(), _componentManager.getComponents<Action>()->get(player_id),
                windowWidth, windowHeight, scene);
            handleSoundSetting(_componentManager.getComponents<Action>()->get(player_id), _componentManager.getComponents<Animation>(), _componentManager.getComponents<Sprite>(),
                _componentManager.getComponents<Button>(), soundState, windowWidth, windowHeight);
        }
    }

    void SettingsMenu::handleSoundSetting(Action &player_action, std::shared_ptr<ComponentMap<Animation>> animationMap, std::shared_ptr<ComponentMap<Sprite>> spriteMap,
        std::shared_ptr<ComponentMap<Button>> buttonMap, bool &soundState, const size_t &windowWidth, const size_t &windowHeight)
    {
        std::shared_ptr<Entity> sound_entities = _entityManager.getEntitiesFromFamily("sound")[0];
        Animation &button_animation = animationMap->get(sound_entities->getId());
        Sprite &button_sprite = spriteMap->get(sound_entities->getId());
        Button &button = buttonMap->get(sound_entities->getId());

        if (_soundState == true && soundState == false) {
            _soundState = false;
            button_animation.animate();
            button_animation.animate();
        }

        float windowWidthSizeRatio = 1440.0 / windowWidth;
        float windowHeightSizeRatio = 810.0 / windowHeight;
        static const Action::MouseType keys[1] = { Action::MouseType::Left };
        Action::KeyState mouse_state = player_action.getMouseKeyState(keys[0]);

        if (button.getButtonStatus() == Button::ButtonStatus::HOVER && mouse_state == Action::KeyState::PRESSED) {
            button.setButtonStatus(Button::ButtonStatus::PRESSED);
        } else {
            if (button.getButtonStatus() == Button::ButtonStatus::PRESSED) {
                button.setButtonStatus(Button::ButtonStatus::RELEASED);
            } else if (button.getButtonStatus() == Button::ButtonStatus::RELEASED) {
                if (mouse_state == Action::KeyState::RELEASED) {
                    soundState = !soundState;
                    _soundState = !_soundState;
                    button.setButtonStatus(Button::ButtonStatus::NONE);
                    button_animation.animate();
                }
            } else {
                if (player_action.getMousePosition().X * windowWidthSizeRatio >= button_sprite.getX() &&
                    player_action.getMousePosition().X * windowWidthSizeRatio <= (button_sprite.getX() + (button_animation.getRectWidth() * button_sprite.getScale())) &&
                    player_action.getMousePosition().Y * windowHeightSizeRatio >= button_sprite.getY() &&
                    player_action.getMousePosition().Y * windowHeightSizeRatio <= (button_sprite.getY() + (button_animation.getRectHeight()) * button_sprite.getScale())) {

                    if (button.getButtonStatus() != Button::ButtonStatus::HOVER) {
                        button_animation.animate();
                        button.setButtonStatus(Button::ButtonStatus::HOVER);
                    }
                } else if (button.getButtonStatus() == Button::ButtonStatus::HOVER) {
                    button_animation.animate();
                    button_animation.animate();
                    button_animation.animate();
                    button.setButtonStatus(Button::ButtonStatus::NONE);
                }
            }
        }
    }

    void SettingsMenu::initSprite() {
        ComponentMap<Sprite> sprite;
        Sprite background_sprite(std::string(ASSETS_DIR)+"Menu-background.png", 0, 0);
        Sprite settings_background_sprite(std::string(ASSETS_DIR)+"settings-bg.png", 80, 10, 1.5);
        Sprite close_button_icon_sprite(std::string(ASSETS_DIR)+"cross-icon.png", 1330, 75);
        Sprite close_button_background_sprite(std::string(ASSETS_DIR)+"small-button-bg.png", 1315, 60);
        Sprite sound_icon_sprite(std::string(ASSETS_DIR)+"sound-icon.png", 955, 270, 0.9);
        Sprite menu_button_background_sprite(std::string(ASSETS_DIR)+"Button-bg.png", 850, 400);
        Sprite exit_button_background_sprite(std::string(ASSETS_DIR)+"Button-bg.png", 850, 550);

        sprite.put(background_sprite, _entityManager.spawnEntity("background")->getId());
        sprite.put(settings_background_sprite, _entityManager.spawnEntity("settings-background")->getId());
        sprite.put(close_button_background_sprite, _entityManager.spawnEntity("icon-button")->getId());
        sprite.put(close_button_icon_sprite, _entityManager.spawnEntity("icon")->getId());
        sprite.put(sound_icon_sprite, _entityManager.spawnEntity("sound")->getId());
        sprite.put(menu_button_background_sprite, _entityManager.spawnEntity("text-button")->getId());
        sprite.put(exit_button_background_sprite, _entityManager.spawnEntity("text-button")->getId());
        _componentManager.registerComponent<Sprite>(sprite);
    }

    void SettingsMenu::initSound() {
        ComponentMap<Sound> sound;
        Sound music(std::string(ASSETS_DIR)+"music.ogg", true, Sound::SoundStatus::PLAY);

        sound.put(music, _entityManager.spawnEntity("music")->getId());
        _componentManager.registerComponent<Sound>(sound);
    }

    void SettingsMenu::initText() {
        ComponentMap<Text> text;
        Text settings_title("SETTINGS", std::string(ASSETS_DIR)+"font.ttf", 625, 20, 40, 1, Text::rgb_t(255, 255, 255));
        Text music_title("MUSIC", std::string(ASSETS_DIR)+"font.ttf", 930, 210, 37, 1, Text::rgb_t(255, 255, 255));
        Text menu_title("MENU", std::string(ASSETS_DIR)+"font.ttf", 947.5, 410, 37, 1, Text::rgb_t(255, 255, 255));
        Text exit_title("EXIT", std::string(ASSETS_DIR)+"font.ttf", 957.5, 560, 37, 1, Text::rgb_t(255, 255, 255));

        text.put(settings_title, _entityManager.getEntitiesFromFamily("settings-background")[0]->getId());
        text.put(music_title, _entityManager.getEntitiesFromFamily("sound")[0]->getId());
        text.put(menu_title, _entityManager.getEntitiesFromFamily("text-button")[0]->getId());
        text.put(exit_title, _entityManager.getEntitiesFromFamily("text-button")[1]->getId());
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
        Animation sound_icon_animation(70, 70, 0, 0, 1, 4, 0, 5, 100);
        Animation text_button_animation(380, 98, 0, 0, 1, 3, 0, 7, 100);

        animation.put(close_button_animation, _entityManager.getEntitiesFromFamily("icon-button")[0]->getId());
        animation.put(close_button_icon_animation, _entityManager.getEntitiesFromFamily("icon")[0]->getId());
        animation.put(sound_icon_animation, _entityManager.getEntitiesFromFamily("sound")[0]->getId());
        animation.put(text_button_animation, _entityManager.getEntitiesFromFamily("text-button")[0]->getId());
        animation.put(text_button_animation, _entityManager.getEntitiesFromFamily("text-button")[1]->getId());
        _componentManager.registerComponent<Animation>(animation);
    }

    void SettingsMenu::initButtons()
    {
        ComponentMap<Button> button;
        Button close_button(0);
        Button exit_button(-1);
        Button menu_button(0);
        Button sound_button(-1);

        button.put(close_button, _entityManager.getEntitiesFromFamily("icon-button")[0]->getId());
        button.put(menu_button, _entityManager.getEntitiesFromFamily("text-button")[0]->getId());
        button.put(exit_button, _entityManager.getEntitiesFromFamily("text-button")[1]->getId());
        button.put(sound_button, _entityManager.getEntitiesFromFamily("sound")[0]->getId());
        _componentManager.registerComponent<Button>(button);
    }
}