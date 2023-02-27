/*
** EPITECH PROJECT, 2023
** AMenu.hpp
** File description:
** AMenu
*/

#ifndef _AMenu_
    #define _AMenu_

    #include "AScene.hpp"

    #include "Button.hpp"

    namespace rtype {
            /**
             * @brief The Abstract fot the Menus
             * 
             */
        class AMenu : public AScene {
            public:

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
                 * @brief Init all Buttons of the Home Game Menu object
                 * 
                 */
                virtual void initButtons() = 0;

                /**
                 * @brief 
                 * 
                 * @param animationMap 
                 * @param spriteMap 
                 * @param buttonMap 
                 * @param player_action 
                 * @param windowWidth 
                 * @param windowHeight 
                 */
                void handleButtons(std::shared_ptr<ComponentMap<Animation>> animationMap,
                        std::shared_ptr<ComponentMap<Sprite>> spriteMap, std::shared_ptr<ComponentMap<Button>> buttonMap,
                        Action &player_action, const size_t &windowWidth, const size_t &windowHeight, size_t &scene) {

                    static const Action::MouseType keys[1] = { Action::MouseType::Left };

                    Action::KeyState mouse_state = player_action.getMouseKeyState(keys[0]);
                    std::vector<std::shared_ptr<Entity>> button_entities = _entityManager.getEntitiesFromFamily("button");

                    for (const auto &button : button_entities) {
                        Animation &button_animation = animationMap->get(button->getId());
                        Sprite &button_sprite = spriteMap->get(button->getId());
                        Button &button_component = buttonMap->get(button->getId());

                        if (button_component.getButtonStatus() == Button::ButtonStatus::HOVER && mouse_state == Action::KeyState::PRESSED) {
                            button_component.setButtonStatus(Button::ButtonStatus::PRESSED);
                        } else
                            button_component.handleInteractions(button_animation, button_sprite, player_action, mouse_state, windowWidth, windowHeight, scene);
                    }
                };

            private:
        };
    }

#endif /* !_AMenu_ */