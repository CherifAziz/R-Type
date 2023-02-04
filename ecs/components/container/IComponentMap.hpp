/*
** EPITECH PROJECT, 2023
** IComponentMap
** File description:
** IComponentMap
*/

#ifndef IComponentMap
    #define _IComponentMap_

    namespace rtype {
        /**
         * @brief The Interface for the ComponentMap
         * 
         */
        class IComponentMap
        {
            public:
                /**
                 * @brief Destroy the IComponentMap object
                 * 
                 */
                virtual ~IComponentMap() = default;

                /**
                 * @brief delete all components from the ComponentMap (must be override)
                 * 
                 * @details this method give the ability to delete all components from every ComponentMap for an entity without having to cast beforehand
                 * 
                 * @param id entity id to delete all the components from
                 */
                virtual void deleteEntityComponents(entity_t id) = 0;
        };
    }

#endif /* !IComponentMap */
