/*
** EPITECH PROJECT, 2023
** ISystem
** File description:
** ISystem
*/

#ifndef _ISystem_
    #define _ISystem_

    #include <string.h>

    #include "IScene.hpp"

    namespace rtype {
        /**
         * @brief Interface for all systems
         * 
         */
        class ISystem {
            public:
                /**
                 * @brief Destroy the Interface object
                 * 
                 */
                virtual ~ISystem() = default;

                /**
                 * @brief init the System (must be override)
                 * 
                 */
                virtual void init() = 0;

                /**
                 * @brief update the System (must be override)
                 * 
                 * @param scene the current scene
                 */
                virtual void update(std::shared_ptr<IScene> &scene) = 0;

                /**
                 * @brief Destroy the system (must be override)
                 * 
                 */
                virtual void destroy() = 0;

                /**
                 * @brief Get the Name object (must be override)
                 * 
                 * @return The name as a const std::string& 
                 */
                virtual const std::string &getName() const = 0;

                /**
                 * @brief check if the game is still playing
                 * 
                 * @return true if the game is still playing, false otherwise
                 */
                virtual bool isGameStillPlaying() = 0;

                /**
                 * @brief Get the Current Scene object
                 * 
                 * @return the current scene as a const size_t&
                 */
                virtual const size_t &getCurrentScene() const = 0;


                /**
                 * @brief check if the game is connected
                 *
                 * @return true if the game is connected, false otherwise
                 */
                virtual bool isConnected() = 0;

        };
    }

#endif /* !_ISystem_ */