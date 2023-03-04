/*
** EPITECH PROJECT, 2023
** Storage
** File description:
** Storage
*/

#ifndef _Storage_
    #define _Storage_

    #include <SFML/Graphics.hpp>

    #include <memory>

    namespace rtype {
        /**
         * @brief Used to stock every properties needed by the different systems
         * 
         */
        class Storage {
            public:
                /**
                 * @brief Delete the copy constructor to prevent copy
                 * 
                 * @param other the other Storage object
                 */
                Storage(Storage &other) = delete;

                /**
                 * @brief Destroy the Storage object
                 * 
                 */
                ~Storage() = default;

                /**
                 * @brief Delete the copy construction operator to prevent copy
                 * 
                 * @param other the other Storage object
                 */
                void operator=(const Storage &other) = delete;

                /**
                 * @brief Get the Storage object and create it if it doesn't exist'
                 * 
                 * @return The storage object as a std::shared_ptr<Storage>
                 */
                static std::shared_ptr<Storage> getStorage()
                {
                    static std::shared_ptr<Storage> _storage(new Storage());

                    return _storage;
                }

                /**
                 * @brief Get the Render Window object
                 * 
                 * @return The window as an sf::RenderWindow
                 */
                sf::RenderWindow &getRenderWindow() { return _window; }

                /**
                 * @brief Get the Window Width object
                 * 
                 * @return the window width as a size_t
                 */
                size_t getWindowWidth() { return _window.getSize().x; }

                /**
                 * @brief Get the Window Height object
                 * 
                 * @return the window height as a size_t
                 */
                size_t getWindowHeight() { return _window.getSize().y; }

                /**
                 * @brief Check if the game is still playing
                 * 
                 * @return true if the game is still playing, false otherwise
                 */
                const bool &isStillPlaying() { return _stillPlaying; }

                /**
                 * @brief Check if the game is still playing
                 *
                 * @return true if the game is still playing, false otherwise
                 */
                const bool &isConnected() { return _connected; }

                /**
                 * @brief Set the Current Scene object
                 * 
                 * @param newScene the new current scene
                 */
                void setCurrentScene(const size_t &newScene) { _currentScene = newScene; }

                /**
                 * @brief Get the Current Scene object
                 * 
                 * @return the current scene as a const size_t&
                 */
                const size_t &getCurrentScene() const { return _currentScene; }

                /**
                 * @brief End the game by setting the playing value to false
                 * 
                 */
                void endGame() { _stillPlaying = false; }

                /**
                 * @brief Set the connect state to true
                 *
                 */
                void connected() { _connected = true; }

            protected:
                /**
                 * @brief Construct a new Storage object
                 * 
                 */
                Storage() = default;

                /**
                 * @brief the window
                 * 
                 */
                sf::RenderWindow _window;

                /**
                 * @brief the game state
                 * 
                 */
                bool _stillPlaying = true;
                /**
                 * @brief the network state
                 *
                 */
                bool _connected = false;

                /**
                 * @brief the game current scene
                 * 
                 */
                size_t _currentScene = 0;
        };
    }

#endif /* !_Storage_ */
