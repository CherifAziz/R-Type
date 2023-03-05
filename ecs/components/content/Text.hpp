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

    namespace rtype {
        /**
         * @brief the Text Component
         * 
         */
        class Text {
            public:
                /**
                 * @brief the color structure
                 * 
                 * @details colors are stored as rgb
                 */
                typedef struct rgb_s {
                    /**
                     * @brief Construct a new rgb structure object
                     * 
                     * @param r the red color value
                     * @param g the green color value
                     * @param b the blue color value
                     */
                    rgb_s(uint16_t r, uint16_t g, uint16_t b) : r(r), g(g), b(b) {}

                    /**
                     * @brief Construct a new rgb structure object (white by default)
                     * 
                     */
                    rgb_s() : r(255), g(255), b(255) {}

                    /**
                     * @brief the red color value
                     * 
                     */
                    uint16_t r;

                    /**
                     * @brief the green color value
                     * 
                     */
                    uint16_t g;

                    /**
                     * @brief the blue color value
                     * 
                     */
                    uint16_t b;

                    /**
                     * @brief check if two color are the same
                     * 
                     * @param other the other color that will be compared
                     * @return true if the two color are the same, false otherwise
                     */
                    bool operator==(const rgb_s& other) const { return r == other.r && g == other.g && b == other.b; }
                } rgb_t;

                /**
                 * @brief Construct a new Text object
                 * 
                 * @param text the text that will be displayed
                 * @param font the font for the displayed text
                 * @param x the x position of the text in the window
                 * @param y the y position of the text in the window
                 * @param characterSize the size of the text's characters
                 * @param scale the scale of the text
                 * @param color the color for the text
                 */
                Text(const std::string &text = "", const std::string &font = "", const size_t &x = 0, const size_t &y = 0, const size_t &characterSize = 30,
                const size_t &scale = 0.75, const rgb_t &color = rgb_s()) : _text(text), _font(font), _x(x), _y(y), _characterSize(characterSize),
                _scale(scale), _color(color) {}

                /**
                 * @brief Destroy the Text object
                 * 
                 */
                ~Text() = default;

                /**
                 * @brief Get the Text object
                 * 
                 * @return the text as a const std::string& 
                 */
                const std::string &getText() const { return _text; }

                /**
                 * @brief Set the Text object
                 * 
                 * @param text the text that will be assigned
                 */
                void setText(const std::string &text) { _text = text; }

                /**
                 * @brief Get the Font object
                 * 
                 * @return the font as a const std::string& 
                 */
                const std::string &getFont() const { return _font; }

                /**
                 * @brief Set the Font object
                 * 
                 * @param font the font that will be assigned
                 */
                void setFont(const std::string &font) { _font = font; }

                /**
                 * @brief Get the Color object
                 * 
                 * @return the color as a const rgb_t& 
                 */
                const rgb_t &getColor() const { return _color; }

                /**
                 * @brief Set the Color object
                 * 
                 * @param color the color that will be assigned
                 */
                void setColor(const rgb_t &color) { _color = color; }

                /**
                 * @brief Get the X position object
                 * 
                 * @return the x position as a const size_t& 
                 */
                const size_t &getX() const { return _x; };

                /**
                 * @brief Get the Y position object
                 * 
                 * @return the y position as a const size_t& 
                 */
                const size_t &getY() const { return _y; };

                /**
                 * @brief Set the Position object
                 * 
                 * @param x the x position that will be assigned
                 * @param y the y position that will be assigned
                 */
                void setPosition(const size_t &x, const size_t &y)
                {
                    _x = x;
                    _y = y;
                }

                /**
                 * @brief Get the Character Size object
                 * 
                 * @return the character size as a const size_t& 
                 */
                const size_t &getCharacterSize() const { return _characterSize; }

                /**
                 * @brief Set the Character Size object
                 * 
                 * @param characterSize the character size that will be assigned
                 */
                void setCharacterSize(const size_t &characterSize) { _characterSize = characterSize; }

                /**
                 * @brief Get the Scale object
                 * 
                 * @return the scale as a const size_t& 
                 */
                const size_t &getScale() const { return _scale; }

                /**
                 * @brief Set the Scale object
                 * 
                 * @param scale the scale that will be assigned
                 */
                void setScale(const size_t &scale) { _scale = scale; }

                /**
                 * @brief check if the text are the same
                 * 
                 * @param other the text that will be compared
                 * @return true if the Text components are the same, false otherwise
                 */
                bool operator==(const Text &other) const
                {
                    return _text == other._text && _font == other._font && _x == other._x && _y == other._y && _characterSize == other._characterSize && _scale == other._scale && _color == other._color;
                }

            protected:
                /**
                 * @brief the text string to display
                 * 
                 */
                std::string _text;

                /**
                 * @brief the font file path for the displayed text
                 * 
                 */
                std::string _font;

                /**
                 * @brief the x position
                 * 
                 */
                size_t _x;

                /**
                 * @brief the y position
                 * 
                 */
                size_t _y;

                /**
                 * @brief the character size
                 * 
                 */
                size_t _characterSize;

                /**
                 * @brief the scale
                 * 
                 */
                size_t _scale;

                /**
                 * @brief the color
                 * 
                 */
                rgb_t _color;
        };
    }

#endif /* !_Text_ */