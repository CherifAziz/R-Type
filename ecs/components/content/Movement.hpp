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
                Movement(const float &xDirection = 0, const float &yDirection = 0) : _xDirection(xDirection), _yDirection(yDirection) {};

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
                const float &getXDirection() const { return _xDirection; };

                /**
                 * @brief Get the Y direction object
                 * 
                 * @return the y direction as a const int& 
                 */
                const float &getYDirection() const { return _yDirection; };

                /**
                 * @brief Set the Direction object
                 * 
                 * @param xDirection the x direction that will be assigned
                 * @param yDirection the y direction that will be assigned
                 */
                void setDirection(const float &xDirection, const float &yDirection)
                {
                    _xDirection = xDirection;
                    _yDirection = yDirection;
                }

                /**
                 * @brief check if the movements are the same
                 * 
                 * @param other the movement that will be compared
                 * @return true if the movement are the same, false otherwise
                 */
                bool operator==(const Movement &other) const
                {
                    return _xDirection == other._xDirection && _yDirection == other._yDirection;
                }

            protected:
                /**
                 * @brief the movement x direction
                 * 
                 */
                float _xDirection;

                /**
                 * @brief the movement y direction
                 * 
                 */
                float _yDirection;
        };
    }

#endif /* !_Movement_ */
