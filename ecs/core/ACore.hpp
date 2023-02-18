/*
** EPITECH PROJECT, 2023
** ACore
** File description:
** ACore
*/

#ifndef _ACore_
    #define _ACore_

    #include <vector>
    #include <memory>

    #include "ICore.hpp"
    #include "ISystem.hpp"
    #include "IScene.hpp"

    #include "ComponentManager.hpp"
    #include "EntityManager.hpp"

    namespace rtype {
        /**
         * @brief Abstract class for RType Core
         * 
         */
        class ACore : public ICore {
            protected:
                /**
                 * @brief the systems
                 * 
                 */
                std::vector<std::shared_ptr<ISystem>> _systems;

                /**
                 * @brief the scenes
                 * 
                 */
                std::vector<std::shared_ptr<IScene>> _scenes;

                /**
                 * @brief the current scene in the vector
                 * 
                 */
                size_t _currentScene;
        };
    }

#endif /* !_ACore_ */
