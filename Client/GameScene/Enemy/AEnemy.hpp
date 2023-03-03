/*
** EPITECH PROJECT, 2023
** AEnemy
** File description:
** AEnemy
*/

#ifndef _AEnemy_
    #define _AEnemy_

    #include "IEnemy.hpp"

    namespace rtype {
        class AEnemy : public IEnemy {
            public:
                /**
                 * @brief Get the Id object
                 * 
                 * @return the id as a const entity_t&
                 */
                const entity_t &getId() const { return _id; }

            protected:
                /**
                 * @brief the hp point of the BasicEnemy
                 * 
                 */
                size_t _hp;

                /**
                 * @brief the id of the enemy
                 * 
                 */
                entity_t _id;
        };
    }

#endif /* !_AEnemy_ */
