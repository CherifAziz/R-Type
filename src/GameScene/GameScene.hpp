/*
** EPITECH PROJECT, 2023
** GameScene
** File description:
** GameScene
*/

#ifndef _GameScene_
    #define _GameScene_

    #include "AScene.hpp"

    #include "Sprite.hpp"
    #include "Action.hpp"
    #include "Animation.hpp"
    #include "Movement.hpp"
    #include "Sound.hpp"

    namespace rtype {
        /**
         * @brief The Scene for main game
         * 
         */
        class GameScene : public AScene {
            public:
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
                 * @brief Init the Game
                 * 
                 */
                void init();

                /**
                 * @brief Update the Game
                 * 
                 */
                void update();

                /**
                 * @brief Destroy the Game Scene components and entities
                 * 
                 */
                void destroy();

                /**
                 * @brief check if the game is still playing
                 * 
                 * @return true if the game is still playing, false otherwise
                 */
                const bool &isGameStillPlaying() const;
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
                void handlePlayerMovement(Sprite &player_sprite, const Movement &player_movement, Action &player_action);

                /**
                 * @brief make player action
                 * 
                 * @param player_sprite the player sprite component
                 * @param player_sound the player sound component
                 * @param player_movement the player movement component
                 * @param player_action the player action component
                 */
                void handlePlayerAction(Sprite &player_sprite, Sound &player_sound, const Movement &player_movement, Action &player_action);
        };
    }

#endif /* !_GameScene_ */