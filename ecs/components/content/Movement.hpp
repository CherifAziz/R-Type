/*
** EPITECH PROJECT, 2023
** Movement
** File description:
** Movement
*/

#ifndef _Movement_
    #define _Movement_

    namespace rtype {
        /**
         * @brief the Movement Component
         * 
         */
        class Movement {
            public:
                /**
                 * @brief Construct a new Movement object
                 * 
                 * @param xDirection the Movement x direction
                 * @param yDirection the Movement y direction
                 */
                Movement(const int &xDirection = 0, const int &yDirection = 0);

                /**
                 * @brief Destroy the Movement object
                 * 
                 */
                ~Movement() = default;

                /**
                 * @brief Get the X direction object
                 * 
                 * @return the x direction as a const int& 
                 */
                const int &getXDirection() const { return _xDirection; };

                /**
                 * @brief Get the Y direction object
                 * 
                 * @return the y direction as a const int& 
                 */
                const int &getYDirection() const { return _yDirection; };

                /**
                 * @brief Set the Direction object
                 * 
                 * @param xDirection the x direction that will be assigned
                 * @param yDirection the y direction that will be assigned
                 */
                void setDirection(const int &xDirection, const int &yDirection);

                /**
                 * @brief check if the movements are the same
                 * 
                 * @param other the movement that will be compared
                 * @return true if the movement are the same, false otherwise
                 */
                bool operator==(const Movement &other) const;

            protected:
                /**
                 * @brief the movement x direction
                 * 
                 */
                int _xDirection;

                /**
                 * @brief the movement y direction
                 * 
                 */
                int _yDirection;
        };
    }

#endif /* !_Movement_ */
