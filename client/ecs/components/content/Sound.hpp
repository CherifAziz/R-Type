/*
** EPITECH PROJECT, 2023
** Sound
** File description:
** Sound
*/

#ifndef _Sound_
    #define _Sound_

    #include <string>

    namespace rtype {
        /**
         * @brief the Sound Component
         * 
         */
        class Sound {
            public:
                /**
                 * @brief The Sound's status
                 * 
                 * @details PLAY if the sound must be played, PLAYING if the sound is playing, PAUSE if the sound is paused, STOP if the sound is stopped
                 */
                enum class SoundStatus {
                    PLAY,
                    PLAYING,
                    PAUSE,
                    STOP
                };

                /**
                 * @brief Construct a new Sound object
                 * 
                 * @param file the sound file path
                 * @param isLooping true if the sound must be looping, false otherwise
                 * @param status the sound starting status : PLAY if the sound must be played, STOP if the sound must not be played at start
                 * it's useless and shouldn't not be done to put the sound status as PLAYING or PAUSE
                 */
                Sound(const std::string &file = "", const bool &isLooping = false, const SoundStatus &status = SoundStatus::PLAY) :
                _file(file), _isLooping(isLooping), _status(status) {}

                /**
                 * @brief Destroy the Sound object
                 * 
                 */
                ~Sound() = default;


                /**
                 * @brief Set the File object
                 * 
                 * @param file the filepath that will be assigned
                 */
                void setFile(const std::string &file) { _file = file; }

                /**
                 * @brief Get the File object
                 * 
                 * @return the filepath as a const std::string& 
                 */
                const std::string &getFile() const { return _file; }

                /**
                 * @brief Set the Loop State object
                 * 
                 * @param isLooping the looping state that will be assigned
                 */
                void setLoopState(bool isLooping) { _isLooping = isLooping; }

                /**
                 * @brief check if the sound is looping
                 * 
                 * @return true if the sound is looping, false otherwise
                 */
                bool isLooping() const { return _isLooping; }

                /**
                 * @brief Set the Status object
                 * 
                 * @param status the status that will be assigned
                 */
                void setStatus(const SoundStatus &status) { _status = status; }

                /**
                 * @brief Get the Status object
                 * 
                 * @return the status as a const SoundStatus& 
                 */
                const SoundStatus& getStatus() const { return _status; }

                /**
                 * @brief check if the sounds are the same
                 * 
                 * @param other the sound that will be compared
                 * @return true if the sounds are the same, false otherwise
                 */
                bool operator==(const Sound& other) const
                {
                    return _file == other._file && _isLooping == other._isLooping && _status == other._status;
                }

            protected:
                /**
                 * @brief the sound filepath
                 * 
                 */
                std::string _file;

                /**
                 * @brief the sound's looping status
                 * 
                 */
                bool _isLooping;

                /**
                 * @brief the sound's status
                 * 
                 */
                SoundStatus _status;
        };
    }

#endif /* !_Sound_ */