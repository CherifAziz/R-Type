/*
** EPITECH PROJECT, 2023
** Button.hpp
** File description:
** Button class
*/

#ifndef _Button_
    #define _Button_

    #include <sys/types.h>
    #include <iostream>

    #include "Action.hpp"
    #include "Sprite.hpp"
    #include "Animation.hpp"
    #include "Text.hpp"

    namespace rtype {
        /**
         * @brief the Button Component
         * 
         */
        class Button {
            public:
                /**
                 * @brief The Button's status
                 * 
                 * @details NONE if nothing is interracting with the button, HOVER if the mouse is hover the button, PRESSED if the mouse click on the button, RELEASE when the mouse release the click on the button
                 */
                enum class ButtonStatus {
                    NONE,
                    HOVER,
                    PRESSED,
                    RELEASED
                };

                /**
                 * @brief Construct a new Button object
                 * 
                 * @param linked_scene the scene position linked with the button ( if the button is clicked, redirect to this scene )
                 * @param status the status of the button
                 */
                Button(size_t linked_scene = 0, ButtonStatus status = ButtonStatus::NONE) :
                _status(status), _linked_scene(linked_scene) {};

                /**
                 * @brief Destroy the Button object
                 * 
                 */
                ~Button() = default;

                /**
                 * @brief Get the Button Status object
                 * 
                 * @return ButtonStatus 
                 */
                ButtonStatus getButtonStatus() { return (this->_status); };

                /**
                 * @brief Get the Button Status object
                 * 
                 * @param status 
                 */
                void setButtonStatus(ButtonStatus status) { this->_status = status; };

                /**
                 * @brief Get the Button Linked scene
                 * 
                 * @return _linked_scene 
                 */
                const size_t &getLinkedScene() const { return (this->_linked_scene); };

                /**
                 * @brief Set the Button Linked Scene
                 * 
                 * @param linked_scene 
                 */
                void setLinkedScene(const size_t &linked_scene) { this->_linked_scene = linked_scene; };

                /**
                 * @brief 
                 * 
                 * @param animation 
                 * @param sprite 
                 * @param mouse_state 
                 * @param windowWidth 
                 * @param windowHeight 
                 */
                void handleIconButtonInteractions(Animation &animation, Animation &icon_animation, Sprite &sprite, Action &player_action, Action::KeyState mouse_state, const size_t &windowWidth, const size_t &windowHeight, size_t &scene)
                {
                    float windowWidthSizeRatio = 1440.0 / windowWidth;
                    float windowHeightSizeRatio = 810.0 / windowHeight;

                    if (this->_status == ButtonStatus::PRESSED) {
                        this->_status = ButtonStatus::RELEASED;
                        animation.animate();
                        icon_animation.animate();
                    } else if (this->_status == ButtonStatus::RELEASED) {
                        if (mouse_state == Action::KeyState::RELEASED) {
                            scene = _linked_scene;
                            this->_status = ButtonStatus::NONE;
                            animation.animate();
                            icon_animation.animate();
                        }
                    } else {
                        if (player_action.getMousePosition().X * windowWidthSizeRatio >= sprite.getX() &&
                            player_action.getMousePosition().X * windowWidthSizeRatio <= (sprite.getX() + (animation.getRectWidth() * sprite.getScale())) &&
                            player_action.getMousePosition().Y * windowHeightSizeRatio >= sprite.getY() &&
                            player_action.getMousePosition().Y * windowHeightSizeRatio <= (sprite.getY() + (animation.getRectHeight()) * sprite.getScale())) {

                            if (this->_status != ButtonStatus::HOVER) {
                                animation.animate();
                                icon_animation.animate();
                                this->_status = ButtonStatus::HOVER;
                            }
                        } else if (this->_status == ButtonStatus::HOVER) {
                            animation.animate();
                            animation.animate();
                            icon_animation.animate();
                            icon_animation.animate();
                            this->_status = ButtonStatus::NONE;
                        }
                    }
                };

                /**
                 * @brief 
                 * 
                 * @param animation 
                 * @param sprite 
                 * @param mouse_state 
                 * @param windowWidth 
                 * @param windowHeight 
                 */
                void handleTextButtonInteractions(Animation &animation, Sprite &sprite, Text &text, Action &player_action, Action::KeyState mouse_state, const size_t &windowWidth, const size_t &windowHeight, size_t &scene)
                {
                    float windowWidthSizeRatio = 1440.0 / windowWidth;
                    float windowHeightSizeRatio = 810.0 / windowHeight;

                    if (this->_status == ButtonStatus::PRESSED) {
                        this->_status = ButtonStatus::RELEASED;
                        animation.animate();
                        text.setColor(Text::rgb_t(0, 0, 0));
                    } else if (this->_status == ButtonStatus::RELEASED) {
                        if (mouse_state == Action::KeyState::RELEASED) {
                            scene = _linked_scene;
                            this->_status = ButtonStatus::NONE;
                            animation.animate();
                            text.setColor(Text::rgb_t(255, 255, 255));
                        }
                    } else {
                        if (player_action.getMousePosition().X * windowWidthSizeRatio >= sprite.getX() &&
                            player_action.getMousePosition().X * windowWidthSizeRatio <= (sprite.getX() + (animation.getRectWidth() * sprite.getScale())) &&
                            player_action.getMousePosition().Y * windowHeightSizeRatio >= sprite.getY() &&
                            player_action.getMousePosition().Y * windowHeightSizeRatio <= (sprite.getY() + (animation.getRectHeight()) * sprite.getScale())) {

                            if (this->_status != ButtonStatus::HOVER) {
                                animation.animate();
                                text.setColor(Text::rgb_t(134, 218, 239));
                                this->_status = ButtonStatus::HOVER;
                            }
                        } else if (this->_status == ButtonStatus::HOVER) {
                            animation.animate();
                            animation.animate();
                            text.setColor(Text::rgb_t(250, 250, 250));
                            this->_status = ButtonStatus::NONE;
                        }
                    }
                };

            protected:
                /**
                 * @brief the button's status
                 * 
                 */
                ButtonStatus _status;

                /**
                 * @brief the position of the scene which is linked with the button
                 * 
                 */
                size_t _linked_scene;
        };
    }

#endif /* !_Button_ */