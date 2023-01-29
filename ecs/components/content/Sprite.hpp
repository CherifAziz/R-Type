/*
** EPITECH PROJECT, 2023
** Sprite
** File description:
** Sprite
*/

#ifndef _Sprite_
    #define _Sprite_

    #include <string>

    class Sprite {
        public:
            Sprite(const std::string &filename = "", const size_t &x = 0, const size_t &y = 0, const size_t &scale = 1) : _filename(filename), _x(x), _y(y), _scale(scale) {};
            ~Sprite() = default;

            const std::string &getFilename() const { return _filename; }
            void setFilename(const std::string &filename) { _filename = filename;}

            const size_t &getX() const {return _x;};
            const size_t &getY() const {return _y;};
            void setPosition(const size_t &x, const size_t &y)
            {
                _x = x;
                _y = y;
            }

            const size_t &getScale() const { return _scale; }
            void setScale(const size_t &scale) { _scale = scale; }

            bool operator==(const Sprite &other) const
            {
                return _filename == other._filename && _x == other._x && _y == other._y && _scale == other._scale;
            }

        protected:
            std::string _filename;
            size_t _x;
            size_t _y;
            size_t _scale;
    };

#endif /* !_Sprite_ */
