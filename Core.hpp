/*
** EPITECH PROJECT, 2023
** Core.hpp
** File description:
** Core structure
*/

#ifndef CoreGuard
    #define CoreGuard

    #include <SFML/Graphics.hpp>

    class Core
    {
        public:
            Core(sf::RenderWindow &tempWindow);
            ~Core();
            int mainLoop();

            void setWindow(sf::VideoMode windowSize, const sf::String &windowName, sf::Uint32 windowStyle);
        private:
            sf::RenderWindow &window;
    };

#endif /* !CoreGuard */
