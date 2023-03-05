/*
** EPITECH PROJECT, 2023
** GameScene
** File description:
** GameScene
*/

#ifndef _GameScene_
    #define _GameScene_

    #define SHIELD_TIME 9000

    #include "AScene.hpp"
    #include "EnemyManager.hpp"

    #include "Sprite.hpp"
    #include "Action.hpp"
    #include "Animation.hpp"
    #include "Movement.hpp"
    #include "Sound.hpp"
    #include "Network.hpp"
    #include "Storage.hpp"

    namespace rtype {
        /**
         * @brief The Scene for main game
         *
         */
        class GameScene : public AScene {
            public:
                enum class BulletLoadState {
                    LITTLE,
                    CHARGED,
                    BIG_CHARGE,
                    SUPER_CHARGE,
                    MEGA_CHARGE,
                    BEBOU_CHARGE
                };

                /**
                 * @brief Construct a new Game Scene object
                 *
                 */
                GameScene();

                /**
                 * @brief Destroy the Game Scene object
                 *
                 */
                ~GameScene();

                /**
                 * @brief Update the Game
                 *
                 * @param time the current time that has been elapsed
                 */
                void update(const int64_t &time, const size_t &windowWidth, const size_t &windowHeight, size_t &scene, size_t &previousScene, bool &soundState);

            protected:
                /**
                 * @brief init the sprite map
                 *
                 * @return the sprite map as a ComponentMap<Sprite>
                 */
                void initSprite();

                /**
                 * @brief init the animation map
                 *
                 * @return the animation map as a ComponentMap<Animation>
                 */
                void initAnimation();

                /**
                 * @brief init the sound map
                 *
                 * @return the sound map as a ComponentMap<Sound>
                 */
                void initSound();

                /**
                 * @brief init the action map
                 *
                 * @return the action map as a ComponentMap<Action>
                 */
                void initAction();

                /**
                 * @brief init the text map
                 *
                 * @return the text map as a ComponentMap<Text>
                 */
                void initText();

                /**
                 * @brief init the collsion map
                 *
                 * @return the collision map as a ComponentMap<Collision>
                 */
                void initCollision();

                /**
                 * @brief init the movement map
                 *
                 * @return the movement map as a ComponentMap<Movement>
                 */
                void initMovement();

                /**
                 * @brief init the network map
                 *
                 */
                void initNetwork();

                void initWaves();

                /**
                 * @brief move the background to create a parallax effect
                 *
                 * @param spriteMap the sprite map
                 * @param movementMap the movement map
                 */
                void handleBackgroundMovement(std::shared_ptr<ComponentMap<Sprite>> spriteMap, const std::shared_ptr<ComponentMap<Movement>> &movementMap);

                /**
                 * @brief move the player according to action component
                 *
                 * @param player_sprite the player sprite component
                 * @param player_movement the player movement component
                 * @param player_action the player action component
                 */
                void handlePlayerMovement(Sprite &player_sprite, Movement &player_movement, Action &player_action, const Animation &player_animation, const size_t &windowWidth, const size_t &windowHeight);

                /**
                 * @brief make player action
                 *
                 * @param player_sprite the player sprite component
                 * @param player_sound the player sound component
                 * @param player_movement the player movement component
                 * @param player_action the player action component
                 */
                void handlePlayerAction(Sprite &player_sprite, Movement &player_movement, Action &player_action, Animation &player_animation, const size_t &windowWidth, const size_t &windowHeight);

                void handleWaves(const int64_t &time, const size_t &windowWidth, const size_t &windowHeight);

                /**
                 * @brief play all scene components animation
                 *
                 * @param animationMap the animation map
                 */
                void playAnimation(std::shared_ptr<ComponentMap<Animation>> animationMap);


                void handleEnemyBulletSpriteSheet(Animation &bullet);
                bool handleEnemyBulletDestruction(Sprite &bullet, entity_t entity);                
                void initEnemyBullet(entity_t entity);
                void callEnemiesSendingBullets(Sprite &player_sprite);
                void spawnEnemyBullet(std::vector<std::shared_ptr<Entity>> &enemies);
                void spawnBossBullet(std::vector<std::shared_ptr<Entity>> &enemies, Sprite &player_sprite);
                void moveEnemyBullet(Sprite &bullet, const Movement &bullet_velocity);
                void handleEnemyBullet(const int64_t &time);

                /**
                 * @brief move shown frame on spritesheet according to player action
                 *
                 * @param bullet
                 */
                void handleBulletSpriteSheet(Animation &bullet);

                /**
                 * @brief destroy dead or outborder bullet
                 *
                 * @param bullet the bullet to check
                 *
                 * @return true if the bullet was destroyed, false otherwise
                 */
                bool handleBulletDestruction(Sprite &bullet, const size_t &windowWidth, entity_t entity);

                /**
                 * @brief move the bullet loading following the player
                 *
                 */
                void updateBulletLoading();

                /**
                 * @brief init the loading of a bullet
                 *
                 */
                void initBulletLoading();

                /**
                 * @brief Init bullet Sprite, Animation, Movement, Sound and Collision
                 *
                 */
                void initBullet(entity_t entity);

                /**
                 * @brief Create a bullet
                 *
                 */
                void spawnBullet(Action &player_action, const Action::KeyState &space_state, const int64_t &time);

                /**
                 * @brief Make bullets movement
                 *
                 * @param bullet the bullet sprite for changing position
                 * @param bullet_velocity the bullet movement x and y velocity
                 */
                void moveBullet(Sprite &bullet, const Movement &bullet_velocity);

                /**
                 * @brief handle bullet display, destruction, movement, animation and collision
                 *
                 */
                void handleBullet(const int64_t &time, Action &player_action, const size_t &windowWidth, entity_t player_id);

                /**
                 * @brief Check if the two element are colliding
                 *
                 * @param x1 the x position of the first element
                 * @param y1 the y position of the first element
                 * @param width1 the width of the first element
                 * @param height1 the height of the first element
                 * @param x2 the x position of the second element
                 * @param y2 the y position of the second element
                 * @param width2 the width of the second element
                 * @param height2 the height of the second element
                 * @return true if there is a collision, false otherwise
                 */
                bool isColliding(size_t x1, size_t y1, size_t width1, size_t height1, size_t x2, size_t y2, size_t width2, size_t height2);

                /**
                 * @brief Check if the element collide with another
                 *
                 * @param id the id of the element
                 *
                 * @return the id of the element touched if there is one, -1 otherwise
                 */
                int handleElementCollision(entity_t id);

                int GetFamilyIndex(const std::string &family);

                typedef struct laps_s {
                    int64_t lastTime = 0;
                    size_t lapsPassed = 0;
                    int64_t prevTime = 0;
                } laps_t;

                bool handleGameTime(const int64_t &wantedLaps, const int64_t &elapsedTime, const std::string &lapsName);

                void initObject(const std::string &family, const entity_t &entity);

                void changePlayerSprite(const bool &shieldStatus, const int64_t &time);

                void initPowerUp(const int &x, const int &y);

                void movePowerUp(Sprite &object, const Movement &object_velocity);

                bool checkPlayerGettingPowerUp(const entity_t &entity, Sprite &object, Animation &object_animation, const int64_t &time);

                void handlePowerUp(const int64_t &time);

                static const std::vector<std::string> BULLET_NAMES;

                BulletLoadState _bulletLoad = BulletLoadState::LITTLE;
                EnemyManager _enemyManager;

                std::shared_ptr<Storage> _storage;

                enum class BulletSentState {
                    SENT,
                    SMALL_DISTANCE,
                    LONG_DISTANCE,
                    SHOOTED
                };

                enum class LoadState {
                    OFF,
                    ON
                } _loadState = LoadState::ON;

                std::unordered_map<entity_t, std::pair<BulletSentState, BulletLoadState>> _bullet_sent;
                std::unordered_map<entity_t, size_t> _bullet_remaining_force;

                std::vector<std::vector<std::pair<std::string, int>>> waves;
                
                size_t _actual_wave = 1;
                size_t _score = 0;

                enum class BulletTimeState {
                    NONE,
                    STARTED,
                    READY
                } _bulletTime = BulletTimeState::NONE;

                size_t _player_hp = 1;

                std::unordered_map<std::string, laps_t> _laps;

                bool _playerShield = false;
        };
    }

#endif /* !_GameScene_ */
