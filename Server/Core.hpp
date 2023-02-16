/*
** EPITECH PROJECT, 2023
** Core.hpp
** File description:
** Core structure
*/

#ifndef CoreGuard
    #define CoreGuard

    #include <cstdlib>
    #include <vector>
    #include <memory>
    #include <boost/asio.hpp>
    #include <boost/bind.hpp>
    #include <boost/date_time/posix_time/posix_time.hpp>
    #include <iostream>

    #include "ICore.hpp"
    #include "ISystem.hpp"
    #include "IScene.hpp"

    #include "Storage.hpp"

    namespace rtype {
        /**
         * @brief the Core class
         *
         */
        class Core : public ICore
        {
            public:
                /**
                 * @brief Construct a new Core object
                 *
                 * @param defaultScene the default scene index
                 */
                Core(size_t defaultScene, boost::asio::io_context &ioc, std::string ip, std::string port);

                /**
                 * @brief Destroy the Core object
                 *
                 */
                ~Core();

                /**
                 * @brief the game loop
                 *
                 * @return int the game return value (84 if an error occured, 0 otherwise)
                 */
                int loopGame();

            private:
                /**
                 * @brief Get the Window Size object
                 *
                 * @return the window size as a const std::pair<size_t, size_t>&
                 */
                std::pair<size_t, size_t> getWindowSize() const;

                /**
                 * @brief the scenes
                 *
                 */
                std::vector<std::shared_ptr<IScene>> _scenes;

                /**
                 * @brief the current scene in the vector
                 *
                 */
                size_t _currentScene;

                /**
                 * @brief the systems
                 *
                 */
                std::vector<std::shared_ptr<ISystem>> _systems;

                /**
                 * @brief the timer
                 *
                 */
                boost::asio::high_resolution_timer _timer;

                /**
                 * @brief the starting time
                 *
                 */
                std::chrono::high_resolution_clock::time_point _starting_time;
        };
    }

#endif /* !CoreGuard */
