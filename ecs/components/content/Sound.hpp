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
            enum class SoundStatus {
                PLAY,
                PAUSE,
                STOP
            };

            Sound(const std::string &file, const bool &isLooping = false, const SoundStatus &status = SoundStatus::STOP) :
            _file(file), _isLooping(isLooping), _status(status) {}
            ~Sound();

            void setFile(const std::string &file) { _file = file; }
            const std::string &getFile() const { return _file; }
            void setLoopState(bool isLooping) { _isLooping = isLooping; }
            bool isLooping() const { return _isLooping; }
            void setStatus(SoundStatus status) { _status = status; }
            const SoundStatus& getStatus() const { return _status; }
        private:
            std::string _file;
            bool _isLooping;
            SoundStatus _status;
    };

#endif /* !_Sound_ */