/*
** EPITECH PROJECT, 2023
** Core.hpp
** File description:
** Core structure
*/

#ifndef CoreGuard
    #define CoreGuard

    #include <SFML/Graphics.hpp>
    #include <vector>
    #include <memory>

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
                 */
                Core();

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
