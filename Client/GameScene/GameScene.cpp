/*
** EPITECH PROJECT, 2023
** GameScene
** File description:
** GameScene
*/

#include "GameScene.hpp"

#include "Collision.hpp"
#include "Text.hpp"
#include "GameValues.hpp"

namespace rtype
{
    GameScene::GameScene()
    {
        initSprite();
        initAnimation();
        initAction();
        initCollision();
        initMovement();
        initSound();
        initText();
        initNetwork();
    }

    GameScene::~GameScene()
    {

    }

    bool GameScene::isColliding(size_t x1, size_t y1, size_t width1, size_t height1, size_t x2, size_t y2, size_t width2, size_t height2)
    {
        if (x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 && height1 + y1 > y2)
            return true;
        return false;
    }

    int GameScene::handleElementCollision(entity_t id)
    {
        Collision collision = _componentManager.get<Collision>(id);
        std::vector<std::string> families = collision.getFamilies();
        std::shared_ptr<ComponentMap<Sprite>> spriteMap = _componentManager.getComponents<Sprite>();
        std::shared_ptr<ComponentMap<Animation>> animationMap = _componentManager.getComponents<Animation>();
        Sprite &sprite = spriteMap->get(id);
        Animation &animation = animationMap->get(id);

        for (auto &family : families) {
            std::vector<std::shared_ptr<Entity>> entities = _entityManager.getEntitiesFromFamily(family);

            for (auto &entity : entities) {
                if (spriteMap->contains(entity->getId()) && animationMap->contains(entity->getId())) {
                    Sprite &enemy_sprite = spriteMap->get(entity->getId());
                    Animation &enemy_animation = animationMap->get(entity->getId());

                    if (isColliding(sprite.getX(), sprite.getY(), animation.getRectWidth() * sprite.getScale(), animation.getRectHeight() * sprite.getScale(),
                                    enemy_sprite.getX(), enemy_sprite.getY(), enemy_animation.getRectWidth() * enemy_sprite.getScale(), enemy_animation.getRectHeight() * enemy_sprite.getScale())) {
                        return entity->getId();
                    }
                }
            }
        }
        return -1;
    }

    void GameScene::update(const int64_t &time, const size_t &windowWidth, const size_t &windowHeight)
    {
        entity_t player_id = _entityManager.getEntitiesFromFamily("player")[0]->getId();
        int value = handleElementCollision(player_id);
        if (value != -1)
            _player_hp -= 1;
        if (_player_hp == 0) {
            std::cout << "THE END" << std::endl;
            exit(0);
        }
        handleBackgroundMovement(_componentManager.getComponents<Sprite>(), _componentManager.getComponents<Movement>());
        handlePlayerAction(_componentManager.getComponents<Sprite>()->get(player_id), _componentManager.getComponents<Movement>()->get(player_id),
        _componentManager.getComponents<Action>()->get(player_id), _componentManager.getComponents<Animation>()->get(player_id), windowWidth, windowHeight);
        handleBullet(time, _componentManager.getComponents<Action>()->get(player_id), windowWidth);
        // handleBasicEnemy(time);
        if (time % 10 == 0)
            playAnimation(_componentManager.getComponents<Animation>());
    }

    void GameScene::initSprite()
    {
        ComponentMap<Sprite> sprite;
        Sprite background_sprite("assets/spacebg.png", 0, 0);
        Sprite second_background_sprite("assets/spacebg.png", 1920, 0);
        Sprite spaceship_sprite("assets/spaceship.gif", 100, 100, 4);

        sprite.put(background_sprite, _entityManager.spawnEntity("background")->getId());
        sprite.put(second_background_sprite, _entityManager.spawnEntity("background")->getId());
        sprite.put(spaceship_sprite, _entityManager.spawnEntity("player")->getId());
        _componentManager.registerComponent<Sprite>(sprite);
    }

    void GameScene::initAnimation()
    {
        ComponentMap<Animation> animation;
        Animation spaceship_animation(PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, PLAYER_X_DEFAULT_SPRITE, 0, 1, 1, 1, 1, 500);

        animation.put(spaceship_animation, _entityManager.getEntitiesFromFamily("player")[0]->getId());
        _componentManager.registerComponent<Animation>(animation);
    }

    void GameScene::initSound()
    {
        ComponentMap<Sound> sound;
        Sound music("assets/music.ogg", true, Sound::SoundStatus::PAUSE);

        sound.put(music, _entityManager.spawnEntity("music")->getId());
        _componentManager.registerComponent<Sound>(sound);
    }

    void GameScene::initText()
    {
        ComponentMap<Text> text;
        Text title("Hi player !", "assets/font.otf", 30, 30, 60, 1, Text::rgb_t(255, 160, 122));

        text.put(title, _entityManager.spawnEntity("title")->getId());
        _componentManager.registerComponent<Text>(text);
    }

    void GameScene::initCollision()
    {
        ComponentMap<Collision> collisionMap;
        Collision collision(ENEMIES);

        collisionMap.put(collision, _entityManager.getEntitiesFromFamily("player")[0]->getId());
        _componentManager.registerComponent<Collision>(collisionMap);
    }

    void GameScene::initMovement()
    {
        ComponentMap<Movement> movement;
        Movement player_move(0, 0);
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
        if (first_sprite.getX() < -1919)
            first_sprite.setPosition(1920, 0);
        else if (second_sprite.getX() < -1919)
            second_sprite.setPosition(1920, 0);
    }

    void GameScene::handlePlayerMovement(Sprite &player_sprite, Movement &player_movement, Action &player_action, const Animation &player_animation,
    const size_t &windowWidth, const size_t &windowHeight)
    {
        static const Action::KeyType keys[4] = {Action::KeyType::Z, Action::KeyType::S, Action::KeyType::Q, Action::KeyType::D};
        static const int x_move[4] = {0, 0, -1, 1};
        static const int y_move[4] = {-1, 1, 0, 0};
        static const int max_boost = 10;

        for (uint16_t it = 0; it < 4; it++) {
            Action::KeyState state = player_action.getKeyState(keys[it]);
            int x_direction = player_movement.getXDirection();
            int y_direction = player_movement.getYDirection();

            if (state != Action::KeyState::UP && state != Action::KeyState::RELEASED) {
                x_direction += 5 * x_move[it];
                if (x_direction <= -max_boost)
                    x_direction = -max_boost;
                else if (x_direction >= max_boost)
                    x_direction = max_boost;

                y_direction += 5 * y_move[it];
                if (y_direction <= -max_boost)
                    y_direction = -max_boost;
                else if (y_direction >= max_boost)
                    y_direction = max_boost;
            }
            player_movement.setDirection(x_direction * 0.9, y_direction * 0.9);
            if (player_sprite.getX() + player_movement.getXDirection() > 0 && player_sprite.getX() + (int)player_animation.getRectWidth() * (int)player_sprite.getScale() + player_movement.getXDirection() < (int)windowWidth
            && player_sprite.getY() + player_movement.getYDirection() > 0 && player_sprite.getY() + (int)player_animation.getRectHeight() * (int)player_sprite.getScale() + player_movement.getYDirection() < (int)windowHeight)
                player_sprite.setPosition(player_sprite.getX() + player_movement.getXDirection(), player_sprite.getY() + player_movement.getYDirection());
        }
    }

    void GameScene::handlePlayerAction(Sprite &player_sprite, Movement &player_movement, Action &player_action, Animation &player_animation, const size_t &windowWidth, const size_t &windowHeight)
    {
        handlePlayerMovement(player_sprite, player_movement, player_action, player_animation, windowWidth, windowHeight);
        if (player_action.getKeyState(Action::KeyType::Z) == Action::KeyState::PRESSED)
            player_animation.setX(PLAYER_X_UP_SPRITE);
        else if (player_action.getKeyState(Action::KeyType::Z) == Action::KeyState::DOWN)
            player_animation.setX(PLAYER_X_UP_PRESSED_SPRITE);
        else if (player_action.getKeyState(Action::KeyType::S) == Action::KeyState::PRESSED)
            player_animation.setX(PLAYER_X_DOWN_SPRITE);
        else if (player_action.getKeyState(Action::KeyType::S) == Action::KeyState::DOWN)
            player_animation.setX(PLAYER_X_DOWN_PRESSED_SPRITE);
        else
            player_animation.setX(PLAYER_X_DEFAULT_SPRITE);
    }

    void GameScene::playAnimation(std::shared_ptr<ComponentMap<Animation>> animationMap)
    {
        for (uint16_t it = 0; it < animationMap->getSize(); it++) {
            Animation &animation = animationMap->getFromIndex(it);

            animation.animate();
        }
    }

    void GameScene::initNetwork()
    {
        ComponentMap<Network> network;
        _componentManager.registerComponent<Network>(network);
    }
}