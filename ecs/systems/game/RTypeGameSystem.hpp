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

    #include "GameScene/GameScene.hpp"

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
                 */
                RTypeGameSystem(const size_t &defaultScene) : AGameSystem("RType", defaultScene)
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
                    _scenes.push_back(std::make_shared<GameScene>());

                    _startingTime = std::chrono::high_resolution_clock::now();
                    _storage = Storage::getStorage();
                }

                /**
                 * @brief update the game system by calling each scenes and changing time for animation
                 * 
                 * @param componentManager the component manager
                 * @param entityManager the entity manager
                 */
                void update(ComponentManager &/*componentManager*/, EntityManager &/*entityManager*/)
                {
                    auto current = std::chrono::high_resolution_clock::now();
                    int64_t elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current - _startingTime).count();

                    if (_scenes[_currentScene]->isGameStillPlaying() == false)
                        return;
                    _scenes[_currentScene]->update(elapsed_time, _storage->getWindowWidth(), _storage->getWindowHeight());
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
                const bool &isGameStillPlaying() const
                {
                    return _scenes[_currentScene]->isGameStillPlaying();
                }

                /**
                 * @brief Get the Component Manager object
                 * 
                 * @return the component manager as a ComponentManager& 
                 */
                ComponentManager &getComponentManager() const
                {
                    return _scenes[_currentScene]->getComponentManager();
                }

                /**
                 * @brief Get the Entity Manager object
                 * 
                 * @return the entity manager as a EntityManager& 
                 */
                EntityManager &getEntityManager() const
                {
                    return _scenes[_currentScene]->getEntityManager();
                }

            protected:

                /**
                 * @brief The starting time of the game system clock
                 * 
                 */
                std::chrono::_V2::system_clock::time_point _startingTime;

                /**
                 * @brief the singleton storage
                 * 
                 */
                std::shared_ptr<Storage> _storage;
        };
    }

#endif /* !_GameSystem_ */