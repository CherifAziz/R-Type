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

    class Storage {
        public:
            Storage(Storage &other) = delete;
            ~Storage() = default;
    
            void operator=(const Storage &other) = delete;

            static std::shared_ptr<Storage> getStorage()
            {
                static std::shared_ptr<Storage> _storage(new Storage());

                return _storage;
            }

            sf::RenderWindow &getRenderWindow() { return _window; }

        protected:
            Storage() = default;

            sf::RenderWindow _window;
    };

#endif /* !_Storage_ */
