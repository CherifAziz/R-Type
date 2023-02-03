/*
** EPITECH PROJECT, 2023
** IInputSystem
** File description:
** IInputSystem
*/

#ifndef _IInputSystem_
    #define _IInputSystem_

    #include <string>

    namespace rtype {
        /**
         * @brief Interface for all InputSystem
         * 
         */
        class IInputSystem {
            public:
                /**
                 * @brief Destroy the IInputSystem object
                 * 
                 */
                virtual ~IInputSystem() = default;

                /**
                 * @brief Get the Library Name object (must be override)
                 * 
                 * @return The library name as a const std::string& 
                 */
                virtual const std::string &getLibraryName() const = 0;
        };
    }

#endif /* !_IInputSystem_ */
