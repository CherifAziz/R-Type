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

    #include "ACore.hpp"
    #include "ISystem.hpp"
    #include "IScene.hpp"

    namespace rtype {
        /**
         * @brief the Core class
         *
         */
        class Core : public ACore
        {
            public:
                /**
                 * @brief Construct a new Core object
                 *
                 * @param defaultScene the default scene index
                 */
                Core(boost::asio::io_context &ioc, std::string ip, std::string port);

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

                /**
                 * @brief Get the game status
                 *
                 * @return true Game is running
                 * @return false Game is stoped
                 */
                bool isGameRunning();

            private:
                /**
                 * @brief Get the Window Size object
                 *
                 * @return the window size as a const std::pair<size_t, size_t>&
                 */
                std::pair<size_t, size_t> getWindowSize() const;

                /**
                 * @brief the timer
                 *
                 */
                boost::asio::high_resolution_timer _timer;
        };
    }

#endif /* !CoreGuard */
