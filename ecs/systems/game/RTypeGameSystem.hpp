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

    #include "GameScene.hpp"

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
                    scenes.push_back(std::make_shared<GameScene>());
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
                    _startingTime = std::chrono::steady_clock::now();
                    _storage = Storage::getStorage();
                }

                /**
                 * @brief update the game system by calling each scenes and changing time for animation
                 *
                 * @param scene the current game scene
                 */
                void update(std::shared_ptr<IScene> &scene)
                {
                    auto current = std::chrono::steady_clock::now();
                    int64_t elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current - _startingTime).count();

                    if (_storage->isStillPlaying() == false)
                        return;
                    scene->update(elapsed_time, _storage->getWindowWidth(), _storage->getWindowHeight());
                    if (elapsed_time >= 100)
                        _startingTime = current;
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
                    return _storage->getRenderWindow().isOpen();
                }

                /**
                 * @brief check the connection status
                 * 
                 * @return true if it's connected to the server, false otherwise
                 */
                bool isConnected()
                {
                    return _storage->isConnected();
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
                std::chrono::steady_clock::time_point _startingTime;

                /**
                 * @brief the singleton storage
                 *
                 */
                std::shared_ptr<Storage> _storage;
        };
    }

#endif /* !_GameSystem_ */