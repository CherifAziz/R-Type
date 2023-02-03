/*
** EPITECH PROJECT, 2023
** IRenderSystem
** File description:
** IRenderSystem
*/

#ifndef _IRenderSystem
    #define _IRenderSystem_

    #include <string.h>

    namespace rtype {
        /**
         * @brief Interface for all RenderSystem
         * 
         */
        class IRenderSystem {
            public:
                /**
                 * @brief Destroy the IRenderSystem object
                 * 
                 */
                virtual ~IRenderSystem() = default;

                /**
                 * @brief init the IRenderSystem (must be override)
                 * 
                 */
                virtual void init() = 0;

                /**
                 * @brief Get the Library Name object (must be override)
                 * 
                 * @return The library name as a const std::string& 
                 */
                virtual const std::string &getLibraryName() const = 0;

                /**
                 * @brief Destroy all rendering components (must be override)
                 * 
                 */
                virtual void destroyRenderingComponents() = 0;
        };
    }

#endif /* !_IRenderSystem */