/*
** EPITECH PROJECT, 2023
** IComponentMap
** File description:
** IComponentMap
*/

#ifndef IComponentMap
    #define _IComponentMap_

    #include "Entity.hpp"

    class IComponentMap
    {
        public:
            virtual ~IComponentMap() = default;
            virtual void delete_entity_components(unsigned long) = 0;
    };

#endif /* !IComponentMap */
