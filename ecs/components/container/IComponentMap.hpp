/*
** EPITECH PROJECT, 2023
** IComponentMap
** File description:
** IComponentMap
*/

#ifndef IComponentMap
    #define _IComponentMap_

    class IComponentMap
    {
        public:
            virtual ~IComponentMap() = default;
            virtual void deleteEntityComponents(unsigned long) = 0;
    };

#endif /* !IComponentMap */
