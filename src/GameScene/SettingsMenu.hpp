/*
** EPITECH PROJECT, 2023
** SettingsMenu.hpp
** File description:
** SettingsMenu
*/

#ifndef _SettingsMenu_
    #define _SettingsMenu_

    #include "AMenu.hpp"

    #include "Sound.hpp"
    #include "Text.hpp"
    #include "Movement.hpp"
    
    namespace rtype {

        class SettingsMenu : public AMenu {
            public:
                
                SettingsMenu();

                ~SettingsMenu();

                void update(const int64_t &time, const size_t &windowWidth, const size_t &windowHeight, size_t &scene, size_t &previousScene);

            protected:

                void initSprite();

                void initSound();

                void initText();

                void initMovement();

                void initAction();

                void initAnimation();

                void initButtons();
        };

    }

#endif /* !_SettingsMenu_ */