/*
** EPITECH PROJECT, 2023
** GameScene
** File description:
** GameScene
*/

#ifndef _GameScene_
    #define _GameScene_

    #include "AScene.hpp"
    #include "EnemyManager.hpp"

    #include "Sprite.hpp"
    #include "Action.hpp"
    #include "Animation.hpp"
    #include "Movement.hpp"
    #include "Sound.hpp"
    #include "Network.hpp"

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
                void update(const int64_t &time, const size_t &windowWidth, const size_t &windowHeight);

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

                void handleWaves(const int64_t &time);

                /**
                 * @brief play all scene components animation
                 *
                 * @param animationMap the animation map
                 */
                void playAnimation(std::shared_ptr<ComponentMap<Animation>> animationMap);


                void handleEnemyBulletSpriteSheet(Animation &bullet);
                bool handleEnemyBulletDestruction(Sprite &bullet, entity_t entity);                
                void initEnemyBullet(entity_t entity);
                void spawnEnemyBullet(std::vector<std::shared_ptr<Entity>> &enemies);
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
                void spawnBullet(Action &player_action, const Action::KeyState &space_state);

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
                void handleBullet(const int64_t &time, Action &player_action, const size_t &windowWidth);

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

                static const std::vector<std::string> ENEMIES;
                static const std::vector<std::string> BULLET_NAMES;

                BulletLoadState _bulletLoad = BulletLoadState::LITTLE;
                EnemyManager _enemyManager;

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

                std::vector<std::vector<std::pair<std::string, int>>> waves;
                
                size_t _actual_wave = 1;
                size_t _score = 0;

                enum class BulletTimeState {
                    NONE,
                    STARTED,
                    LOADING1,
                    LOADING2,
                    LOADING3,
                    LOADING4,
                    LOADING5,
                    READY
                } _bulletTime = BulletTimeState::NONE;

                size_t _player_hp = 1;
        };
    }

#endif /* !_GameScene_ */