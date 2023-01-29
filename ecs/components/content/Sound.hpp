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
                PLAYING,
                PAUSE,
                STOP
            };

            Sound(const std::string &file = "", const bool &isLooping = false, const SoundStatus &status = SoundStatus::PLAY) :
            _file(file), _isLooping(isLooping), _status(status) {}
            ~Sound() = default;

            void setFile(const std::string &file) { _file = file; }
            const std::string &getFile() const { return _file; }
            void setLoopState(bool isLooping) { _isLooping = isLooping; }
            bool isLooping() const { return _isLooping; }
            void setStatus(const SoundStatus &status) { _status = status; }
            const SoundStatus& getStatus() const { return _status; }

            bool operator==(const Sound& other) const
            {
                return _file == other._file && _isLooping == other._isLooping && _status == other._status;
            }

        protected:
            std::string _file;
            bool _isLooping;
            SoundStatus _status;
    };

#endif /* !_Sound_ */