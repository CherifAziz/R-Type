/*
** EPITECH PROJECT, 2023
** GameScene
** File description:
** GameScene
*/

#include "GameScene.hpp"

#include "Collision.hpp"
#include "Text.hpp"

namespace rtype
{
    GameScene::GameScene()
    {
    }

    GameScene::~GameScene()
    {
    }

    void GameScene::init()
    {
        initSprite();
        initAnimation();
        initAction();
        initCollision();
        initMovement();
        initSound();
        initText();
    }

    void GameScene::update()
    {
        entity_t player_id = _entityManager.getEntitiesFromFamily("player")[0]->getId();

        handleBackgroundMovement(_componentManager.getComponents<Sprite>(), _componentManager.getComponents<Movement>());
        handlePlayerAction(_componentManager.getComponents<Sprite>()->get(player_id), _componentManager.getComponents<Sound>()->get(player_id),
        _componentManager.getComponents<Movement>()->get(player_id), _componentManager.getComponents<Action>()->get(player_id));
    }

    void GameScene::destroy()
    {
    }

    const bool &GameScene::isGameStillPlaying() const
    {
        return _entityManager.isGamePlaying();
    }

    void GameScene::initSprite()
    {
        ComponentMap<Sprite> sprite;
        Sprite background_sprite("assets/spacebg.png", 0, 0);
        Sprite second_background_sprite("assets/spacebg.png", 1920, 0);
        Sprite bird_sprite("assets/birds.png", 100, 100);

        sprite.put(background_sprite, _entityManager.spawnEntity("background")->getId());
        sprite.put(second_background_sprite, _entityManager.spawnEntity("background")->getId());
        sprite.put(bird_sprite, _entityManager.spawnEntity("player")->getId());
        _componentManager.registerComponent<Sprite>(sprite);
    }

    void GameScene::initAnimation()
    {
        ComponentMap<Animation> animation;
        Animation bird_animation(199, 134, 0, 0, 4, 1, 0, 0, 500);

        animation.put(bird_animation, _entityManager.getEntitiesFromFamily("player")[0]->getId());
        _componentManager.registerComponent<Animation>(animation);
    }

    void GameScene::initSound()
    {
        ComponentMap<Sound> sound;
        Sound music("assets/music.ogg", true, Sound::SoundStatus::PLAY);
        Sound pow("assets/pow.ogg", false, Sound::SoundStatus::STOP);

        sound.put(music, _entityManager.spawnEntity("music")->getId());
        sound.put(pow, _entityManager.getEntitiesFromFamily("player")[0]->getId());
        _componentManager.registerComponent<Sound>(sound);
    }

    void GameScene::initText()
    {
        ComponentMap<Text> text;
        Text title("The title bro", "assets/font.otf", 30, 30, 60, 1, Text::rgb_t(255, 160, 122));

        text.put(title, _entityManager.spawnEntity("title")->getId());
        _componentManager.registerComponent<Text>(text);
    }

    void GameScene::initCollision()
    {

    }

    void GameScene::initMovement()
    {
        ComponentMap<Movement> movement;
        Movement player_move(1, 1);
        Movement first_background_movement(1, 1);
        Movement second_background_movement(1, 1);

        movement.put(player_move, _entityManager.getEntitiesFromFamily("player")[0]->getId());
        movement.put(first_background_movement, _entityManager.getEntitiesFromFamily("background")[0]->getId());
        movement.put(second_background_movement, _entityManager.getEntitiesFromFamily("background")[1]->getId());
        _componentManager.registerComponent<Movement>(movement);
    }

    void GameScene::initAction()
    {
        ComponentMap<Action> action;
        Action player_action;

        action.put(player_action, _entityManager.getEntitiesFromFamily("player")[0]->getId());
        _componentManager.registerComponent<Action>(action);
    }

    void GameScene::handleBackgroundMovement(std::shared_ptr<ComponentMap<Sprite>> spriteMap, const std::shared_ptr<ComponentMap<Movement>> &movementMap)
    {
        entity_t first_background = _entityManager.getEntitiesFromFamily("background")[0]->getId();
        entity_t second_background = _entityManager.getEntitiesFromFamily("background")[1]->getId();
        Sprite &first_sprite = spriteMap->get(first_background);
        Sprite &second_sprite = spriteMap->get(second_background);
        Movement &first_movement = movementMap->get(first_background);
        Movement &second_movement = movementMap->get(second_background);

        first_sprite.setPosition(first_sprite.getX() - first_movement.getXDirection(), first_sprite.getY());
        second_sprite.setPosition(second_sprite.getX() - second_movement.getXDirection(), second_sprite.getY());
        if (first_sprite.getX() < -1920)
            first_sprite.setPosition(1920, 0);
        else if (second_sprite.getX() < -1920)
            second_sprite.setPosition(1920, 0);
    }

    void GameScene::handlePlayerMovement(Sprite &player_sprite, const Movement &player_movement, Action &player_action)
    {
        static const Action::KeyType keys[4] = {Action::KeyType::Z, Action::KeyType::S, Action::KeyType::Q, Action::KeyType::D};
        static const ssize_t x_move[4] = {0, 0, -1, 1};
        static const ssize_t y_move[4] = {-1, 1, 0, 0};

        for (uint16_t it = 0; it < 4; it++) {
            Action::KeyState state = player_action.getKeyState(keys[it]);
            ssize_t x_movement = x_move[it] * player_movement.getXDirection() * (int)state;
            ssize_t y_movement = y_move[it] * player_movement.getYDirection() * (int)state;

            // if (it == 3)
                // std::cout << (int)state << std::endl;
            x_movement -= x_movement * (1 - (float)state / 10);
            y_movement -= y_movement * (1 - (float)state / 10);
            if (state != Action::KeyState::UP && state != Action::KeyState::RELEASED) {
                player_sprite.setPosition(player_sprite.getX() + x_movement, player_sprite.getY() + y_movement);
                if (state != Action::KeyState::DOWN10)
                    player_action.setState(keys[it], (Action::KeyState)((int)state + 1));
            }
        }
    }

    void GameScene::handlePlayerAction(Sprite &player_sprite, Sound &player_sound, const Movement &player_movement, Action &player_action)
    {
        Action::KeyState space_state = player_action.getKeyState(Action::KeyType::SPACE);

        if (space_state == Action::KeyState::PRESSED && player_sound.getStatus() != Sound::SoundStatus::PLAY && player_sound.getStatus() != Sound::SoundStatus::PLAYING)
            player_sound.setStatus(Sound::SoundStatus::PLAY);
        handlePlayerMovement(player_sprite, player_movement, player_action);
    }
}