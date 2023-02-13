/*
** EPITECH PROJECT, 2023
** HomeMenuScene.hpp
** File description:
** HomeMenuScene
*/

#ifndef _HomeMenuScene_
    #define _HomeMenuScene_

    #include "AMenu.hpp"

    #include "Sound.hpp"
    #include "Text.hpp"
    #include "Movement.hpp"
    
    namespace rtype {

        class HomeMenuScene : public AMenu {
            public:
                
                HomeMenuScene();

                ~HomeMenuScene();

                void update(const int64_t &time);

                void destroy();

                const bool &isGameStillPlaying() const;

            protected:

                void initSprite();

                void initSound();

                void initText();

                void initMovement();

                void initAction();

                void initAnimation();

            private:
        };

    }

#endif /* !_HomeMenuScene_ */