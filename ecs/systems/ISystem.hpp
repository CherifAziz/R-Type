/*
** EPITECH PROJECT, 2023
** ISystem
** File description:
** ISystem
*/

#ifndef _ISystem_
    #define _ISystem_

    #include <string.h>

    #include "ComponentManager.hpp"
    #include "EntityManager.hpp"

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
                 * @param componentManager 
                 * @param entityManager 
                 */
                virtual void update(ComponentManager &componentManager, EntityManager &entityManager) = 0;

                /**
                 * @brief Destroy the system (must be override)
                 * 
                 */
                virtual void destroy() = 0;

                /**
                 * @brief Get the Library Name object (must be override)
                 * 
                 * @return The library name as a const std::string& 
                 */
                virtual const std::string &getLibraryName() const = 0;

                /**
                 * @brief Get the Window Size object
                 * 
                 * @return the window size as an const std::pair<size_t, size_t>& 
                 */
                virtual std::pair<size_t, size_t> getWindowWSize() const = 0;
        };
    }

#endif /* !_ISystem_ */