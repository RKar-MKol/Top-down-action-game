#ifndef UNIT_H
#define UNIT_H

#include <Object.h>

enum Direction{LEFT,RIGHT,DOWN,UP,
NOT_LEFT,NOT_RIGHT,NOT_DOWN,NOT_UP}; // do Move3()

class Unit : public Object
{
    public:
        Unit(sf::Vector2f Position,float radius);
        void MovePLS();
        sf::Vector2f GetRotation() {return Rotation;}
        void SetRotation(sf::Vector2f Rotation) {this->Rotation = Rotation;}
        ~Unit();

    private:

        //Velocity odpowiada za przesuniecie
        sf::Vector2f Velocity;
        //Rotation to wektor jednostkowy oznaczający kierunek
        sf::Vector2f Rotation;
        float MovementSpeed;


};

#endif // UNIT_H
