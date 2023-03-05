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
    #include "Storage.hpp"

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
                RTypeGameSystem(std::vector<std::shared_ptr<IScene>> &scenes);

                /**
                 * @brief Destroy the Game System object
                 *
                 */
                ~RTypeGameSystem();

                /**
                 * @brief init the RType Game System object
                 *
                 * @details Add the game scenes, start the clock and get the singleton storage
                 */
                void init();

                /**
                 * @brief update the game system by calling each scenes and changing time for animation
                 *
                 * @param scene the current game scene
                 */
                void update(std::shared_ptr<IScene> &scene);

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
                bool isGameStillPlaying();
                /**
                 * @brief Get the Current Scene object
                 *
                 * @return the current scene as a const size_t&
                 */
                const size_t &getCurrentScene() const;

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