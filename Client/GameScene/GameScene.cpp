/*
** EPITECH PROJECT, 2023
** GameScene
** File description:
** GameScene
*/

#include "GameScene.hpp"
#include "EnemyManager.hpp"

#include <iostream>
#include <fstream>
#include <string>
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
        initWaves();
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

    bool GameScene::handleGameTime(const int64_t &wantedLaps, const int64_t &elapsedTime, const std::string &lapsName)
    {
        if (_laps.count(lapsName) == 0)
            _laps[lapsName] = {0, 0};
        if (_laps[lapsName].lapsPassed * wantedLaps >= elapsedTime) {
            _laps[lapsName].lapsPassed = 0;
        } else if (_laps[lapsName].lastTime >= wantedLaps) {
            _laps[lapsName].lapsPassed += 1;
            _laps[lapsName].lastTime = 0;
            _laps[lapsName].prevTime = elapsedTime;
            return true;
        } else if (elapsedTime == _laps[lapsName].prevTime)
            return true;
        else
            _laps[lapsName].lastTime = elapsedTime - _laps[lapsName].lapsPassed * wantedLaps;
        _laps[lapsName].prevTime = elapsedTime;
        return false;
    }

    void GameScene::update(const int64_t &time, const size_t &windowWidth, const size_t &windowHeight)
    {
        entity_t player_id = _entityManager.getEntitiesFromFamily("player")[0]->getId();
        int value = handleElementCollision(player_id);

        if (value != -1 && _playerShield == false)
            _player_hp -= 1;
        if (_player_hp == 0) {
            std::cout << "THE END" << std::endl;
            exit(0);
        }
        handlePlayerAction(_componentManager.getComponents<Sprite>()->get(player_id), _componentManager.getComponents<Movement>()->get(player_id),
        _componentManager.getComponents<Action>()->get(player_id), _componentManager.getComponents<Animation>()->get(player_id), windowWidth, windowHeight);
        handleWaves(time, windowWidth, windowHeight);
        handleEnemyBullet(time);
        handleBullet(time, _componentManager.getComponents<Action>()->get(player_id), windowWidth);
        handlePowerUp(time);
        handleBackgroundMovement(_componentManager.getComponents<Sprite>(), _componentManager.getComponents<Movement>());
        if (handleGameTime(100, time, "animationLaps"))
            playAnimation(_componentManager.getComponents<Animation>());
        else if (handleGameTime(400, time, "enemyBulletSpawn"))
            callEnemiesSendingBullets(_componentManager.getComponents<Sprite>()->get(player_id));
    }

    void GameScene::initSprite()
    {
        ComponentMap<Sprite> sprite;
        Sprite background_sprite("assets/spacebg.png", 0, 0);
        Sprite second_background_sprite("assets/spacebg.png", 1920, 0);
        Sprite spaceship_sprite("assets/powerup.gif", 100, 100, 4);

        sprite.put(background_sprite, _entityManager.spawnEntity("background")->getId());
        sprite.put(second_background_sprite, _entityManager.spawnEntity("background")->getId());
        sprite.put(spaceship_sprite, _entityManager.spawnEntity("player")->getId());
        _componentManager.registerComponent<Sprite>(sprite);
    }

    void GameScene::initAnimation()
    {
        ComponentMap<Animation> animation;
        Animation spaceship_animation(PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, PLAYER_X_DEFAULT_SPRITE, 2, 1, 1, 1, 2, 500);

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
        Text title("Level "+ std::to_string(_actual_wave), "assets/font.otf", 30, 30, 60, 1, Text::rgb_t(255, 160, 122));
        Text score("SCORE: " + std::to_string(_score), "assets/font.otf", 30, 900, 50, 1, Text::rgb_t(255, 199, 17));

        text.put(title, _entityManager.spawnEntity("title")->getId());
        text.put(score, _entityManager.spawnEntity("score")->getId());
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

    void GameScene::initWaves()
    {
        std::string line;
        std::vector<std::pair<std::string, int>> wave_config;

        std::ifstream wave_file("assets/wave.txt");

        if (wave_file.is_open()) {
            while (std::getline(wave_file, line)) 
            {
                if (line.empty()) {
                    waves.push_back(wave_config);
                    wave_config.clear();
                }
                else if (wave_file.eof() && !line.empty()) {
                    std::string enemy;
                    std::string nbrOfEnemy;
                    std::stringstream ss(line);
                    std::getline(ss, enemy, ',');
                    std::getline(ss, nbrOfEnemy, ',');
                    wave_config.push_back(std::make_pair(enemy, std::stoi(nbrOfEnemy)));
                    waves.push_back(wave_config);
                    wave_config.clear();
                }
                else {
                    std::string enemy;
                    std::string nbrOfEnemy;
                    std::stringstream ss(line);
                    std::getline(ss, enemy, ',');
                    std::getline(ss, nbrOfEnemy, ',');
                    wave_config.push_back(std::make_pair(enemy, std::stoi(nbrOfEnemy)));
                }
            }
            wave_file.close();
        }

        for (int i = 0; i < waves.size(); i++) {
            for (int j = 0; j < waves[i].size(); j++) {
                std::cout << waves[i][j].first << " ";
                std::cout << waves[i][j].second << " ";
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    }

    void GameScene::handleWaves(const int64_t &time, const size_t &windowWidth, const size_t &windowHeight)
    {
        entity_t text_id = _entityManager.getEntitiesFromFamily("title")[0]->getId();
        entity_t score_id = _entityManager.getEntitiesFromFamily("score")[0]->getId();
        std::shared_ptr<ComponentMap<Text>> textMap = _componentManager.getComponents<Text>();

        Text &title = textMap->get(text_id);
        Text &score = textMap->get(score_id);
        int wave_finish = 0;

        score.setText("Score: "+ std::to_string(_score));
        if (waves.size() >= 1) {
            for (int j = 0; j < waves[0].size(); j++) {
                if (waves[0][j].second != 0)
                    wave_finish = 1;
            }
            if (wave_finish == 0 && waves.size() == 1)
                title.setText("The end");
            if (wave_finish == 0 && waves.size() != 1) {
                _actual_wave += 1;
                title.setText("Level "+ std::to_string(_actual_wave));
                waves.erase(waves.begin());
            }
            for (int j = 0; j < waves[0].size(); j++) {
                if (waves[0][j].second > 0)
                    _enemyManager.createEnemy(waves[0][j].first, _componentManager, _entityManager, windowWidth, windowHeight);
            }
            _enemyManager.handleEnemies(time, _componentManager, _entityManager, windowWidth, windowHeight);
        }
    }

    int GameScene::GetFamilyIndex(const std::string &family)
    {
        auto& wave = waves[0];
        auto it = std::find_if(wave.begin(), wave.end(), [&](auto& p) {
            return p.first == family;
        });
        if (it != wave.end())
            return(it - wave.begin());
        else {
            std::cout << "Could not find " << family << std::endl;
            return(-1);
        }
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
            player_movement.setDirection((int)x_direction * 0.9, (int)y_direction * 0.9);
            if (player_sprite.getX() + (int)player_movement.getXDirection() >= 0 && player_sprite.getX() + (int)player_animation.getRectWidth() * (int)player_sprite.getScale() + (int)player_movement.getXDirection() <= (int)windowWidth
            && player_sprite.getY() + (int)player_movement.getYDirection() >= 0 && player_sprite.getY() + (int)player_animation.getRectHeight() * (int)player_sprite.getScale() + (int)player_movement.getYDirection() <= (int)windowHeight)
                player_sprite.setPosition(player_sprite.getX() + player_movement.getXDirection(), player_sprite.getY() + player_movement.getYDirection());
            if (state == Action::KeyState::PRESSED)
                player_action.setState(keys[it], Action::KeyState::DOWN);
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