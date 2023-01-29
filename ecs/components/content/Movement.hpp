/*
** EPITECH PROJECT, 2023
** Movement
** File description:
** Movement
*/

#ifndef _Movement_
    #define _Movement_

    class Movement {
        public:
            Movement(const int &xDirection = 0, const int &yDirection = 0) : _xDirection(xDirection), _yDirection(yDirection) {};
            ~Movement() = default;

            const int &getXDirection() const { return _xDirection; };
            const int &getYDirection() const { return _yDirection; };
            void setDirection(const int &xDirection, const int &yDirection)
            {
                _xDirection = xDirection;
                _yDirection = yDirection;
            }

            bool operator==(const Movement &other) const
            {
                return _xDirection == other._xDirection && _yDirection == other._yDirection;
            }

        protected:
            int _xDirection;
            int _yDirection;
    };

#endif /* !_Movement_ */
