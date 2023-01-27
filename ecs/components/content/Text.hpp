/*
** EPITECH PROJECT, 2023
** Text
** File description:
** Text
*/

#ifndef _Text_
    #define _Text_

    #include <string>
    #include <stddef.h>

    class Text {
        public:
            typedef struct rgb_s {
                rgb_s() : r(255), g(255), b(255) {}
                uint16_t r;
                uint16_t g;
                uint16_t b;
            } rgb_t;

            Text(const std::string &text, const std::string &font, const size_t &x = 0, const size_t &y = 0, const size_t &characterSize = 30,
            const size_t &scale = 1, const rgb_t &color = rgb_s()) : _text(text), _font(font), _x(x), _y(y), _characterSize(characterSize),
            _scale(scale), _color(color) {}
            ~Text();

            const std::string &getText() const { return _text; }
            void setText(const std::string &text) { _text = text; }
            const std::string &getFont() const { return _font; }
            void setFont(const std::string &font) { _font = font; }
            const rgb_t &getColor() const { return _color; }
            void setColor(const rgb_t &color) { _color = color; }

            const size_t &getX() const { return _x; };
            const size_t &getY() const { return _y; };
            void setPosition(const size_t &x, const size_t &y)
            {
                _x = x;
                _y = y;
            }

            const size_t &getCharacterSize() const { return _characterSize; }
            void setCharacterSize(const size_t &characterSize) { _characterSize = characterSize; }
            const size_t &getScale() const { return _scale; }
            void setScale(const size_t &scale) { _scale = scale; }

        private:
            std::string _text;
            std::string _font;
            size_t _x;
            size_t _y;
            size_t _characterSize;
            size_t _scale;
            rgb_t _color;
    };

#endif /* !_Text_ */