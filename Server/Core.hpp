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

    #include "ISystem.hpp"
    #include "ACore.hpp"

    #include "Storage.hpp"

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

                /**
                 * @brief check if the game is still running
                 *
                 * @return true if the game is still running, false otherwise
                 */
                bool isGameRunning();

                /**
                 * @brief clear the systems cache between scene
                 * 
                 */
                void clearSystemCache();
        };
    }

#endif /* !CoreGuard */
