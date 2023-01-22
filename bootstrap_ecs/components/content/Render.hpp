/*
** EPITECH PROJECT, 2023
** Render
** File description:
** Render
*/

#ifndef _Render_
    #define _Render_

    #include <string>

    class Render {
        public:
            Render(const std::string &filename = "", const ssize_t &x = 0, const ssize_t &y = 0) : _filename(filename), _x(x), _y(y) {};
            ~Render(){};

            const std::string &get_filename() const { return _filename; }
            void set_filename(const std::string &filename) { _filename = filename;}

            const ssize_t &get_x() const {return _x;};
            const ssize_t &get_y() const {return _y;};
            void set_position(const ssize_t &x, const ssize_t &y)
            {
                _x = x;
                _y = y;
            }
        private:
            std::string _filename;
            ssize_t _x;
            ssize_t _y;
    };

#endif /* !_Render_ */
