/*
** EPITECH PROJECT, 2023
** Animation
** File description:
** Animation
*/

#ifndef _Animation_
    #define _Animation_

    #include <sys/types.h>

    class Animation {
        public:
            Animation(const ssize_t &rectWidth = 30, const ssize_t &rectHeight = 30, const ssize_t &x = 0, const ssize_t &y = 0, const size_t &horizontalPictureNb = 3,
            const size_t &verticalPictureNb = 1, const size_t &horizontalSeparator = 0, const size_t &verticalSeparator = 0, const size_t &delay = 1) :
            _rectWidth(rectWidth), _rectHeight(rectHeight), _x(x), _y(y), _horizontalPictureNb(horizontalPictureNb), _verticalPictureNb(verticalPictureNb),
            _horizontalSeparator(horizontalSeparator), _verticalSeparator(verticalSeparator), _delay(delay) {}
            ~Animation();

            void setRectWidth(const ssize_t &rectWidth) { _rectWidth = rectWidth; }
            const ssize_t &getRectWidth() const { return _rectWidth; }
            void setRectHeight(const ssize_t &rectHeight) { _rectHeight = rectHeight; }
            const ssize_t &getRectHeight() const { return _rectHeight; }

            void setX(const ssize_t &x) { _x = x; }
            const ssize_t &getX() const { return _x; }
            void setY(const ssize_t &y) { _y = y; }
            const ssize_t &getY() const { return _y; }

            void setHorizontalPictureNb(const size_t &horizontalPictureNb) { _horizontalPictureNb = horizontalPictureNb; }
            const size_t &getHorizontalPictureNb() const { return _horizontalPictureNb; }
            void setVerticalPictureNb(const size_t &verticalPictureNb) { _verticalPictureNb = verticalPictureNb; }
            const size_t &getVerticalPictureNb() const { return _verticalPictureNb; }

            void setHorizontalSeparator(const size_t &horizontalSeparator) { _horizontalSeparator = horizontalSeparator; }
            const size_t &getHorizontalSeparator() { return _horizontalSeparator; }
            void setVerticalSeparator(const size_t &verticalSeparator) { _verticalSeparator = verticalSeparator; }
            const size_t &getVerticalSeparator() { return _verticalSeparator; }

            void setDelay(const ssize_t &delay) { _delay = delay; }
            const ssize_t &getDelay() const { return _delay; }

            void animate()
            {
                if (_x > (_horizontalPictureNb - 1) * (_rectWidth + _horizontalSeparator)) {
                    if (_y > (_verticalPictureNb - 1) * (_rectHeight + _verticalSeparator)) {
                        _x = 0;
                        _y = 0;
                        return;
                    }
                    _x = 0;
                    _y += _rectHeight + _verticalSeparator;
                    return;
                }
                _x += _rectWidth + _horizontalSeparator;
            }

        private:
            ssize_t _rectWidth;
            ssize_t _rectHeight;
            ssize_t _x;
            ssize_t _y;
            size_t _horizontalPictureNb;
            size_t _verticalPictureNb;
            size_t _horizontalSeparator;
            size_t _verticalSeparator;
            size_t _delay;
    };

#endif /* !_Animation_ */