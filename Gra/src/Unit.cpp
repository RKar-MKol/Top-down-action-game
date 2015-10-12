#include "Unit.h"

Unit::Unit(sf::Vector2f Position,float radius) : Object(Position,radius)
{
    Rotation = sf::Vector2f(0,0);
    MovementSpeed = 2.0f;
}

 void Unit::MovePLS()
{
    //POZYCJA STARTOWA
    sf::Vector2f start = Position;

    //NORMALIZACJA WEKTORA ROTATION
	double l = sqrt(Rotation.x*Rotation.x+Rotation.y*Rotation.y);
    if(l!=0)
        {Rotation.x/=l; Rotation.y/=l;}
    else
        {Rotation.x=0;Rotation.y=0;}

    //ZMIANA POLOZENIA
	Velocity = Rotation*MovementSpeed;
	Position+=Velocity;

    //JESLI KOLIZJA TO WRACAMY
    if(CheckForCollisions())
    {
        Position = start;
    }
    //USTAWIANIE POZYCJI PROSTOKATA POMOCNICZEGO
    rect.setPosition(Position);
}

Unit::~Unit()
{
    //dtor
}
