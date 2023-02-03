/*
** EPITECH PROJECT, 2023
** ARenderSystem
** File description:
** ARenderSystem
*/

#ifndef _ARenderSystem_
    #define _ARenderSystem_

    #include "IRenderSystem.hpp"

    namespace rtype {
        /**
         * @brief Abstract for all Render System
         * 
         */
        class ARenderSystem : public IRenderSystem {
            public:
                /**
                 * @brief Construct a new ARenderSystem (used by the children class)
                 * 
                 * @param libraryName the rendering library name
                 */
                ARenderSystem(const std::string &libraryName) : _libraryName(libraryName) {}

                /**
                 * @brief Get the Library Name object
                 * 
                 * @return the library name as a const std::string& 
                 */
                const std::string &getLibraryName() const
                {
                    return _libraryName;
                }
            protected:
                /**
                 * @brief the library name
                 * 
                 */
                std::string _libraryName;
        };
    }

#endif /* !_ARenderSystem_ */