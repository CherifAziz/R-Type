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
        class IInputSystem {
            public:
                virtual ~IInputSystem() = default;

                virtual const std::string &getLibraryName() const = 0;
        };
    }

#endif /* !_IInputSystem_ */
