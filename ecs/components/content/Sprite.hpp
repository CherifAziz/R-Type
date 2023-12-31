/*
** EPITECH PROJECT, 2023
** Sprite
** File description:
** Sprite
*/

#ifndef _Sprite_
    #define _Sprite_

    #include <string>

    namespace rtype {
        /**
         * @brief the Sprite Component
         * 
         */
        class Sprite {
            public:
                /**
                 * @brief Construct a new Sprite object
                 * 
                 * @param filename the image filename path
                 * @param x the x position of the sprite in the window
                 * @param y the y position of the sprite in the window
                 * @param scale the scale of the sprite
                 */
                Sprite(const std::string &filename = "", const int &x = 0, const int &y = 0, const float &scale = 0.75);

                /**
                 * @brief Destroy the Sprite object
                 * 
                 */
                ~Sprite();

                /**
                 * @brief Get the Filename object
                 * 
                 * @return the image filepath as a const std::string& 
                 */
                const std::string &getFilename() const { return _filename; }

                /**
                 * @brief Set the Filename object
                 * 
                 * @param filename the filepath of the image that will be assigned
                 */
                void setFilename(const std::string &filename) { _filename = filename;}

                /**
                 * @brief Get the X position object
                 * 
                 * @return the x position as a const int&
                 */
                const int &getX() const {return _x;};

                /**
                 * @brief Get the Y position object
                 * 
                 * @return the y position as a const std::int&
                 */
                const int &getY() const {return _y;};

                /**
                 * @brief Set the Position object
                 * 
                 * @param x the x position that will be assigned
                 * @param y the y position that will be assigned
                 */
                void setPosition(const int &x, const int &y);

                /**
                 * @brief Get the Scale object
                 * 
                 * @return the scale as a const size_t& 
                 */
                const float &getScale() const { return _scale; }

                /**
                 * @brief Set the Scale object
                 * 
                 * @param scale the scale that will be assigned
                 */
                void setScale(const float &scale) { _scale = scale; }

                /**
                 * @brief check if the sprites are the same
                 * 
                 * @param other the sprite that will be compared
                 * @return true if the sprites are the same, false otherwise
                 */
                bool operator==(const Sprite &other) const
                {
                    return _filename == other._filename && _x == other._x && _y == other._y && _scale == other._scale;
                }

            protected:
                /**
                 * @brief the image filepath
                 * 
                 */
                std::string _filename;

                /**
                 * @brief the x position of the sprite
                 * 
                 */
                int _x;

                /**
                 * @brief the y position of the sprite
                 * 
                 */
                int _y;

                /**
                 * @brief the scale of the sprite
                 * 
                 */
                float _scale;
        };
    }

#endif /* !_Sprite_ */
