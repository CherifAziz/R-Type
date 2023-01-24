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
                uint16_t r;
                uint16_t g;
                uint16_t b;
            } rgb_t;

            Text(const std::string &text, const std::string &font, const uint16_t &r = 255, const uint16_t &g = 255, const uint16_t &b = 255) : _text(text), _font(font)
            {
                _color.r = r;
                _color.g = g;
                _color.b = b;
            }
            Text(const std::string &text, const std::string &font, const rgb_t &color) : _text(text), _font(font), _color(color) {}
            ~Text();

            const std::string &getText() const { return _text; }
            void setText(const std::string &text) { _text = text; }
            const std::string &getFont() const { return _font; }
            void setFont(const std::string &font) { _font = font; }
            const rgb_t &getColor() const { return _color; }
            void setColor(const rgb_t &color) { _color = color; }

        private:
            std::string _text;
            std::string _font;
            rgb_t _color;
    };

#endif /* !_Text_ */