/*
** EPITECH PROJECT, 2023
** ICore.hpp
** File description:
** ICore structure
*/

#ifndef ICoreDef
    #define ICoreDef

    namespace rtype {
        /**
         * @brief the Interface Core class
         *
         */
        class ICore
        {
            public:
                /**
                 * @brief Destroy the ICore object
                 *
                 */
                virtual ~ICore() = default;

                /**
                 * @brief the game loop
                 *
                 * @return int the game return value (84 if an error occured, 0 otherwise)
                 */
                virtual int loopGame() = 0;
        };
    }

#endif /* !ICoreDef */
