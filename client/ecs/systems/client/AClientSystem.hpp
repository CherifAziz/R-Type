/*
** EPITECH PROJECT, 2023
** AClientSystem
** File description:
** AClientSystem
*/

#ifndef _AClientSystem_
    #define _AClientSystem_

    namespace rtype {
        /**
         * @brief Abstract for all ClientSystem
         *
         */
        class AClientSystem {
            public:
                /**
                 * @brief Construct a new AClientSystem (used by the children class)
                 *
                 * @param libraryName the client library name
                 */
                AClientSystem(const std::string &libraryName) : _libraryName(libraryName) {}

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

#endif /* _AClientSystem_ */