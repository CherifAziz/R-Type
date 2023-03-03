/*
** EPITECH PROJECT, 2023
** InputButton.hpp
** File description:
** InputButton class
*/

#ifndef _InputButton_
    #define _InputButton_

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
        class InputButton {
            public:
                /**
                 * @brief The Button's status
                 * 
                 * @details NONE if nothing is interracting with the button, HOVER if the mouse is hover the button, PRESSED if the mouse click on the button, RELEASE when the mouse release the click on the button
                 */
                enum class InputButtonStatus {
                    NONE,
                    HOVER,
                    PRESSED,
                    RELEASED,
                    ERROR,
                    VALID
                };

                /**
                 * @brief Construct a new InputButton object
                 * 
                 * @param linked_scene the scene position linked with the button ( if the button is clicked, redirect to this scene )
                 * @param status the status of the button
                 */
                InputButton(size_t linked_scene = 0, InputButtonStatus status = InputButtonStatus::NONE) :
                _status(status) {};

                /**
                 * @brief Destroy the InputButton object
                 * 
                 */
                ~InputButton() = default;

            protected:
                /**
                 * @brief the input button's status
                 * 
                 */
                InputButtonStatus _status;
        };
    }

#endif /* !_InputButton_ */