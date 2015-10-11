#ifndef UNIT_H
#define UNIT_H

#include <Object.h>

enum Direction{LEFT,RIGHT,DOWN,UP,
NOT_LEFT,NOT_RIGHT,NOT_DOWN,NOT_UP}; // do Move3()

class Unit : public Object
{
    public:
        Unit(sf::Vector2f Position,float radius);
        void Move(Direction dir); // 4 kierunki

        // RUCH Z VELOCITY
        void Move2(Direction dir);
        void UpdatePosition2();
        // RUCH Z VELOCITY

        // RUCH Z VELOCITY I UZYWAJAC RELEASED
        void Move3(Direction dir);
        void UpdatePosition3();

        virtual ~Unit();
    private:
        float MovementSpeed;
        sf::Vector2f Velocity2;
        sf::Vector2f Velocity3;
};

#endif // UNIT_H
