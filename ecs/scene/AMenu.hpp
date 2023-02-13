/*
** EPITECH PROJECT, 2023
** AMenu.hpp
** File description:
** AMenu
*/

#ifndef _AMenu_
    #define _AMenu_

    #include "AScene.hpp"

    #include "Action.hpp"
    #include "Sprite.hpp"
    #include "Animation.hpp"

    namespace rtype {
            /**
             * @brief The Abstract fot the Menus
             * 
             */
        class AMenu : public AScene {
            public:
                /**
                 * @brief Init the game
                 * 
                 */
                void init() {
                    initSprite();
                    initSound();
                    initText();
                    initMovement();
                    initAction();
                    initAnimation();
                };

            protected:
                /**
                 * @brief Init all Sprites of the Home Game Menu object
                 * 
                 */
                virtual void initSprite() = 0;

                /**
                 * @brief Init all Sounds of the Home Game Menu object
                 * 
                 */
                virtual void initSound() = 0;

                /**
                 * @brief Init all Texts of the Home Game Menu object
                 * 
                 */
                virtual void initText() = 0;

                /**
                 * @brief Init all Movements of the Home Game Menu object
                 * 
                 */
                virtual void initMovement() = 0;

                /**
                 * @brief init all Actions of the Home Game Menu object
                 * 
                 */
                virtual void initAction() = 0;

                /**
                 * @brief init all Animations of the Home Game Menu object
                 * 
                 */
                virtual void initAnimation() = 0;

                /**
                 * @brief Check every interactions with buttons
                 * 
                 * @param player_action the player action component
                 */
                void handleButtons(std::shared_ptr<ComponentMap<Animation>> animationMap, std::shared_ptr<ComponentMap<Sprite>> spriteMap, Action &player_action) {
                    static const Action::MouseType keys[1] = { Action::MouseType::Left };
                    Action::KeyState state = player_action.getMouseKeyState(keys[0]);
                    std::vector<std::shared_ptr<Entity>> button_entities = _entityManager.getEntitiesFromFamily("button");

                    for (const auto &button : button_entities) {
                        Animation &button_animation = animationMap->get(button->getId());
                        Sprite &button_sprite = spriteMap->get(button->getId());

                        //std   ::cout << button_animation.getRectWidth() << std::endl;
                        std::cout << player_action.getMousePosition().X << " - " << player_action.getMousePosition().Y << std::endl;
                        //std::cout << button_sprite.getX() * button_sprite.getScale() << " - " << button_sprite.getY() * button_sprite.getScale() << std::endl;
                        //std::cout << button_sprite.getX() + button_animation.getRectWidth() << " - " << button_sprite.getY() + button_animation.getRectHeight() << std::endl;
                        if (player_action.getMousePosition().X >= (button_sprite.getX()) &&
                            player_action.getMousePosition().X <= (button_sprite.getX() + (button_animation.getRectWidth() * button_sprite.getScale())) &&
                            player_action.getMousePosition().Y >= (button_sprite.getY()) &&
                            player_action.getMousePosition().Y <= (button_sprite.getY() + (button_animation.getRectHeight()) * button_sprite.getScale() ))
                            std::cout << "Hover Button" << std::endl;
                    }
                    if (state != Action::KeyState::UP && state != Action::KeyState::RELEASED) {
                        std::cout << "Mouse Pressed" << std::endl;
                    }
                };

            private:
        };
    }

#endif /* !_AMenu_ */