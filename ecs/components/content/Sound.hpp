/*
** EPITECH PROJECT, 2023
** Sound
** File description:
** Sound
*/

#ifndef _Sound_
    #define _Sound_

    #include <string>

    class Sound {
        public:
            Sound(const std::string &file, const bool &isLooping = false) : _file(file), _isLooping(isLooping) {}
            ~Sound();

            void setFile(const std::string &file) { _file = file; }
            const std::string &getFile() const { return _file; }
            void setLoopState(bool isLooping) { _isLooping = isLooping; }
            bool isLooping() const { return _isLooping; }
        private:
            std::string _file;
            bool _isLooping;
    };

#endif /* !_Sound_ */