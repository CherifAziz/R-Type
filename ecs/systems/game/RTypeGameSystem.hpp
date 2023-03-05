/*
** EPITECH PROJECT, 2023
** GameSystem
** File description:
** GameSystem
*/

#ifndef _GameSystem_
    #define _GameSystem_

    #include <chrono>

    #include "AGameSystem.hpp"
    #include "IScene.hpp"

    #include "HomeMenuScene.hpp"
    #include "GameScene.hpp"
    #include "Storage.hpp"
    #include "SettingsMenu.hpp"

    namespace rtype {
        /**
         * @brief The Game System for RType video game
         *
         */
        class RTypeGameSystem : public AGameSystem {
            public:
                /**
                 * @brief Construct a new Game System object
                 *
                 * @param scenes the vector of scenes to initialize all scenes
                 *
                 */
                RTypeGameSystem(std::vector<std::shared_ptr<IScene>> &scenes) : AGameSystem("RType")
                {
                }

                /**
                 * @brief Destroy the Game System object
                 *
                 */
                ~RTypeGameSystem()
                {

                }

                /**
                 * @brief init the RType Game System object
                 *
                 * @details Add the game scenes, start the clock and get the singleton storage
                 */
                void init()
                {
                    _startingTime = std::chrono::high_resolution_clock::now();
                    _storage = Storage::getStorage();
                }

                /**
                 * @brief update the game system by calling each scenes and changing time for animation
                 *
                 * @param scene the current game scene
                 */
                void update(std::shared_ptr<IScene> &scene)
                {
                    auto current = std::chrono::high_resolution_clock::now();
                    int64_t elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current - _startingTime).count();
                    size_t scene_id = _storage->getCurrentScene();
                    size_t previous_scene_id = _storage->getPreviousScene();
                    bool soundState = _storage->getSoundState();

                    if (_storage->getRenderWindow().isOpen() == false)
                        return;
                    scene->update(elapsed_time, _storage->getWindowWidth(), _storage->getWindowHeight(), scene_id, previous_scene_id, soundState);
                    if (elapsed_time >= 10000)
                        _startingTime = current;
                    if (soundState != _storage->getSoundState())
                        _storage->setSoundState(soundState);
                    if (scene_id == (size_t)-1)
                        _storage->getRenderWindow().close();
                    else if (scene_id != _storage->getCurrentScene()) {
                        _storage->setPreviousScene(_storage->getCurrentScene());
                        _storage->setCurrentScene(scene_id);
                    }
                }

                /**
                 * @brief destroy the game system
                 *
                 */
                void destroy()
                {

                }

                /**
                 * @brief check if the game is still playing
                 *
                 * @return true if the game is still playing, false otherwise
                 */
                bool isGameStillPlaying()
                {
                    return _storage->getRenderWindow().isOpen() && _storage->isStillPlaying();
                }

                /**
                 * @brief Get the Current Scene object
                 *
                 * @return the current scene as a const size_t&
                 */
                const size_t &getCurrentScene() const
                {
                    return _storage->getCurrentScene();
                }

            protected:

                /**
                 * @brief The starting time of the game system clock
                 *
                 */
                std::chrono::high_resolution_clock::time_point _startingTime;

                /**
                 * @brief the singleton storage
                 *
                 */
                std::shared_ptr<Storage> _storage;
        };
    }

#endif /* !_GameSystem_ */