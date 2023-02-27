/*
** EPITECH PROJECT, 2023
** Animation
** File description:
** Animation
*/

#ifndef _Animation_
    #define _Animation_

    #include <sys/types.h>

    namespace rtype {
        /**
         * @brief the Animation Component
         * 
         */
        class Animation {
            public:
                /**
                 * @brief Construct a new Animation object
                 * 
                 * @param rectWidth the frame's width in the sprite sheet
                 * @param rectHeight the frame's height in the sprite sheet
                 * @param x the x position of the first frame in the sprite sheet
                 * @param y the y position of the first frame in the sprite sheet
                 * @param horizontalPictureNb the number of frames horizontally in the sprite sheet
                 * @param verticalPictureNb the number of frames vertically in the sprite sheet
                 * @param horizontalSeparator the size of separator between frames horizontally
                 * @param verticalSeparator the size of separator between frames vertically
                 * @param delay the delay between every animation (in milliseconds)
                 */
                Animation(const size_t &rectWidth = 30, const size_t &rectHeight = 30, const size_t &x = 0, const size_t &y = 0, const size_t &horizontalPictureNb = 3,
                const size_t &verticalPictureNb = 1, const size_t &horizontalSeparator = 0, const size_t &verticalSeparator = 0, const size_t &delay = 1) :
                _rectWidth(rectWidth), _rectHeight(rectHeight), _x(x), _y(y), _horizontalPictureNb(horizontalPictureNb), _verticalPictureNb(verticalPictureNb),
                _horizontalSeparator(horizontalSeparator), _verticalSeparator(verticalSeparator), _delay(delay), _defaultX(x), _defaultY(y) {}

                /**
                 * @brief Destroy the Animation object
                 * 
                 */
                ~Animation() = default;

                /**
                 * @brief Set the Rect Width object
                 * 
                 * @param rectWidth the rect width that will be assigned
                 */
                void setRectWidth(const size_t &rectWidth) { _rectWidth = rectWidth; }

                /**
                 * @brief Get the Rect Width object
                 * 
                 * @return the rect width as a const size_t& 
                 */
                const size_t &getRectWidth() const { return _rectWidth; }

                /**
                 * @brief Set the Rect Height object
                 * 
                 * @param rectHeight the rect height that will be assigned
                 */
                void setRectHeight(const size_t &rectHeight) { _rectHeight = rectHeight; }

                /**
                 * @brief Get the Rect Height object
                 * 
                 * @return the rect height as a const size_t& 
                 */
                const size_t &getRectHeight() const { return _rectHeight; }

                /**
                 * @brief Set the X position object
                 * 
                 * @param x the x position that will be assigned
                 */
                void setX(const size_t &x) { _x = x; }

                /**
                 * @brief Get the X position object
                 * 
                 * @return the x position as a const size_t& 
                 */
                const size_t &getX() const { return _x; }

                /**
                 * @brief Set the Y position object
                 * 
                 * @param y the y position that will be assigned
                 */
                void setY(const size_t &y) { _y = y; }

                /**
                 * @brief Get the Y position object
                 * 
                 * @return the y position as a const size_t& 
                 */
                const size_t &getY() const { return _y; }

                /**
                 * @brief Set the number of frames horizontally in the sprite sheet
                 * 
                 * @param horizontalPictureNb the number of frames horizontally in the sprite sheet that will be assigned
                 */
                void setHorizontalPictureNb(const size_t &horizontalPictureNb) { _horizontalPictureNb = horizontalPictureNb; }

                /**
                 * @brief Get the the number of frames horizontally in the sprite sheet
                 * 
                 * @return the number of frames horizontally in the sprite sheet as a const size_t&
                 */
                const size_t &getHorizontalPictureNb() const { return _horizontalPictureNb; }

                /**
                 * @brief Set the number of frames vertically in the sprite sheet
                 * 
                 * @param verticalPictureNb the number of frames vertically in the sprite sheet that will be assigned
                 */
                void setVerticalPictureNb(const size_t &verticalPictureNb) { _verticalPictureNb = verticalPictureNb; }

                /**
                 * @brief Get the number of frames vertically in the sprite sheet
                 * 
                 * @return the number of frames vertically in the sprite sheet as a const size_t&
                 */
                const size_t &getVerticalPictureNb() const { return _verticalPictureNb; }

                /**
                 * @brief Set the size of separator between frames horizontally
                 * 
                 * @param horizontalSeparator the size of separator between frames horizontally that will be assigned
                 */
                void setHorizontalSeparator(const size_t &horizontalSeparator) { _horizontalSeparator = horizontalSeparator; }

                /**
                 * @brief Get the size of separator between frames horizontally
                 * 
                 * @return the size of separator between frames horizontally as a const size_t& 
                 */
                const size_t &getHorizontalSeparator() { return _horizontalSeparator; }

                /**
                 * @brief Set the size of separator between frames vertically
                 * 
                 * @param verticalSeparator the size of separator between frames vertically that will be assigned
                 */
                void setVerticalSeparator(const size_t &verticalSeparator) { _verticalSeparator = verticalSeparator; }

                /**
                 * @brief Get the size of separator between frames vertically
                 * 
                 * @return the size of separator between frames vertically as a const size_t& 
                 */
                const size_t &getVerticalSeparator() { return _verticalSeparator; }

                /**
                 * @brief Set the Delay object
                 * 
                 * @param delay the delay that will be assigned (in milliseconds)
                 */
                void setDelay(const int &delay) { _delay = delay; }

                /**
                 * @brief Get the Delay object
                 * 
                 * @return the delay as a const size_t& (in milliseconds)
                 */
                const size_t &getDelay() const { return _delay; }

                /**
                 * @brief move to the next frame
                 * 
                 * @details change the x and y position according to the other's parameters to go to the next frame
                 */
                void animate()
                {
                    if (_horizontalPictureNb == 1 && _verticalPictureNb == 1)
                        return;
                    _x += _rectWidth + _horizontalSeparator;
                    if (_x > _defaultX + (_horizontalPictureNb - 1) * (_rectWidth + _horizontalSeparator)) {
                        _x = _defaultX;
                        _y += _rectHeight + _verticalSeparator;
                        if (_y > _defaultY + (_verticalPictureNb - 1) * (_rectHeight + _verticalSeparator)) {
                            _x = _defaultX;
                            _y = _defaultY;
                        }
                    }
                }

                /**
                 * @brief check if the animation components are the same
                 * 
                 * @param other the animation component that will be compared
                 * @return true if the components are the same, false otherwise
                 */
                bool operator==(const Animation &other) const
                {
                    return _rectWidth == other._rectWidth && _rectHeight == other._rectHeight && _x == other._x && _y == other._y
                    && _horizontalPictureNb == other._horizontalPictureNb && _verticalPictureNb == other._verticalPictureNb
                    && _horizontalSeparator == other._horizontalSeparator && _verticalSeparator == other._verticalSeparator && _delay == other._delay
                    && _defaultX == other._defaultX && _defaultY == other._defaultY;
                }

                /**
                 * @brief set an Animation as the one given in parameter
                 * 
                 * @param other the Animation to take information from
                 * @return the returned animation as an Animation& 
                 */
                Animation &operator=(const Animation &other)
                {
                    _rectWidth = other._rectWidth;
                    _rectHeight = other._rectHeight;
                    _x = other._x;
                    _y = other._y;
                    _horizontalPictureNb = other._horizontalPictureNb;
                    _verticalPictureNb = other._verticalPictureNb;
                    _horizontalSeparator = other._horizontalSeparator;
                    _verticalSeparator = other._verticalSeparator;
                    _delay = other._delay;
                    _defaultX = other._defaultX;
                    _defaultY = other._defaultY;
                    return *this;
                }

            protected:

                /**
                 * @brief the frame's width in the sprite sheet
                 * 
                 */
                size_t _rectWidth;

                /**
                 * @brief the frame's height in the sprite sheet
                 * 
                 */
                size_t _rectHeight;

                /**
                 * @brief the x position of the first frame in the sprite sheet
                 * 
                 */
                size_t _x;

                /**
                 * @brief the y position of the first frame in the sprite sheet
                 * 
                 */
                size_t _y;

                /**
                 * @brief the number of frames horizontally in the sprite sheet
                 * 
                 */
                size_t _horizontalPictureNb;

                /**
                 * @brief the number of frames vertically in the sprite sheet
                 * 
                 */
                size_t _verticalPictureNb;

                /**
                 * @brief the size of separator between frames horizontally
                 * 
                 */
                size_t _horizontalSeparator;

                /**
                 * @brief the size of separator between frames vertically
                 * 
                 */
                size_t _verticalSeparator;

                /**
                 * @brief the delay between every animation (in milliseconds)
                 * 
                 */
                size_t _delay;

                /**
                 * @brief the default x value
                 * 
                 */
                size_t _defaultX;

                /**
                 * @brief the default y value
                 * 
                 */
                size_t _defaultY;
        };
    }

#endif /* !_Animation_ */