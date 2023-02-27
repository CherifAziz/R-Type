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
                 * @brief 
                 * 
                 * @param animation 
                 * @param sprite 
                 * @param mouse_state 
                 * @param windowWidth 
                 * @param windowHeight 
                 */
                void handleInteractions(Animation &animation, Sprite &sprite, Action &player_action, Action::KeyState mouse_state, const size_t &windowWidth, const size_t &windowHeight, size_t &scene)
                {
                    float windowWidthSizeRatio = 1920.0 / windowWidth;
                    float windowHeightSizeRatio = 1020.0 / windowHeight;

                    if (this->_status == ButtonStatus::PRESSED) {
                        this->_status = ButtonStatus::RELEASED;
                        animation.animate();
                    } else if (this->_status == ButtonStatus::RELEASED) {
                        if (mouse_state == Action::KeyState::RELEASED) {
                            scene = _linked_scene;
                            this->_status = ButtonStatus::NONE;
                            animation.animate();
                        }
                    } else {
                        if (player_action.getMousePosition().X * windowWidthSizeRatio >= sprite.getX() &&
                            player_action.getMousePosition().X * windowWidthSizeRatio <= (sprite.getX() + (animation.getRectWidth() * sprite.getScale())) &&
                            player_action.getMousePosition().Y * windowHeightSizeRatio >= sprite.getY() &&
                            player_action.getMousePosition().Y * windowHeightSizeRatio <= (sprite.getY() + (animation.getRectHeight()) * sprite.getScale())) {
                        
                            if (this->_status != ButtonStatus::HOVER) {
                                animation.animate();
                                this->_status = ButtonStatus::HOVER;
                            }
                        } else if (this->_status == ButtonStatus::HOVER) {
                            animation.animate();
                            animation.animate();
                            this->_status = ButtonStatus::NONE;
                        }
                    }
                };

                void handleClick(Animation &animation, Sprite &sprite, Action::KeyState mouse_state)
                {
                    if (this->_status == ButtonStatus::HOVER) {
                        this->_status == ButtonStatus::PRESSED;
                        animation.animate();
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

            private:
        };
    }

#endif /* !_Button_ */