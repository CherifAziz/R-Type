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
            Sprite(const std::string &filename = "", const ssize_t &x = 0, const ssize_t &y = 0, const size_t &scale = 1) : _filename(filename), _x(x), _y(y), _scale(scale) {};
            ~Sprite() = default;

            const std::string &getFilename() const { return _filename; }
            void setFilename(const std::string &filename) { _filename = filename;}

            const ssize_t &getX() const {return _x;};
            const ssize_t &getY() const {return _y;};
            void setPosition(const ssize_t &x, const ssize_t &y)
            {
                _x = x;
                _y = y;
            }

            const size_t &getScale() const { return _scale; }
            void setScale(const size_t &scale) { _scale = scale; }

        private:
            std::string _filename;
            ssize_t _x;
            ssize_t _y;
            size_t _scale;
    };

#endif /* !_Sprite_ */
