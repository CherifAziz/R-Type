/*
** EPITECH PROJECT, 2023
** SfmlInputSystem
** File description:
** SfmlInputSystem
*/

#ifndef _SfmlInputSystem_
    #define _SfmlInputSystem_

    #include <SFML/Graphics.hpp>

    #include "AInputSystem.hpp"

    class SfmlInputSystem : public AInputSystem {
        public:
            SfmlInputSystem() : AInputSystem("Sfml") {}
            ~SfmlInputSystem();

            
        protected:
    };

#endif /* !_SfmlInputSystem_ */