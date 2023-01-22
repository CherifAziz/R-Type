/*
** EPITECH PROJECT, 2023
** IComponentMap
** File description:
** IComponentMap
*/

#ifndef IComponentMap
    #define _IComponentMap_

    typedef unsigned long entity_t;

    class IComponentMap
    {
        public:
            virtual ~IComponentMap() = default;
            virtual void delete_entity_components(const entity_t &) = 0;
    };

#endif /* !IComponentMap */
