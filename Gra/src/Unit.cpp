#include "Unit.h"

Unit::Unit(sf::Vector2f Position,float radius) : Object(Position,radius)
{
    Velocity2 = sf::Vector2f(0,0);
    Velocity3 = Velocity2;
    MovementSpeed = 10.0f;
}

void Unit::Move(Direction dir)
{

    sf::Vector2f start;
    float startingX = Position.x;
    float startingY = Position.y;
    start = Position;
    //if(Collision==Circle) start = CircleCenter;
    switch(dir)
    {
    case LEFT:
        Position.x-=MovementSpeed;
        //if(Collision==Circle) CircleCenter.x-=MovementSpeed;
        break;
    case RIGHT:
        Position.x+=MovementSpeed;
        //if(Collision==Circle) CircleCenter.x+=MovementSpeed;
        break;
    case DOWN:
        Position.y+=MovementSpeed;
        //if(Collision==Circle) CircleCenter.y+=MovementSpeed;
        break;
    case UP:
        Position.y-=MovementSpeed;
        //if(Collision==Circle) CircleCenter.y-=MovementSpeed;
        break;
    }
    if(CheckForCollisions())
    {
        Position = sf::Vector2f(startingX,startingY);
        //if(Collision==Circle) CircleCenter = start;
    }
    //cout<<Position.x<<" "<<Position.y<<endl;
    rect.setPosition(Position);
    //cout<<rect.getPosition().x<<" "<<rect.getPosition().y<<endl;

}

void Unit::Move2(Direction dir)
{


    switch(dir)
    {
    case LEFT:
        Velocity2.x= -1 *MovementSpeed;
        break;
    case RIGHT:
        Velocity2.x= MovementSpeed;
        break;
    case DOWN:
        Velocity2.y= MovementSpeed;
        break;
    case UP:
        Velocity2.y= -1 *MovementSpeed;
        break;
    }
}
void Unit::UpdatePosition2()
{
    float Przesuniecie = 0.5f;
    if(Velocity2.x == 0 && Velocity2.y == 0 )
        return;
    sf::Vector2f start;
    float startingX = Position.x;
    float startingY = Position.y;
    //if(Collision==Circle) start = CircleCenter;

    Position.x+=Velocity2.x;
    Position.y+=Velocity2.y;
    //CircleCenter.x+=Velocity2.x;
    //CircleCenter.y+=Velocity2.y;

    if(Velocity2.x < 0)
    {
        Velocity2.x+= Przesuniecie;
        if(Velocity2.x > 0)
            Velocity2.x = 0;

    }
    else if(Velocity2.x > 0)
    {
        Velocity2.x-= Przesuniecie;
        if(Velocity2.x < 0 )
            Velocity2.x = 0;
    }

    if(Velocity2.y < 0)
    {
        Velocity2.y+= Przesuniecie;
        if(Velocity2.y > 0)
            Velocity2.y = 0;
    }
    else if(Velocity2.y > 0)
    {
        Velocity2.y-= Przesuniecie;
        if(Velocity2.y < 0 )
            Velocity2.y = 0;
    }



    if(CheckForCollisions())
    {
        Position = sf::Vector2f(startingX,startingY);
        //if(Collision==Circle) CircleCenter = start;
    }
    rect.setPosition(Position);
}
void Unit::Move3(Direction dir)
{

    switch(dir)
    {
    case LEFT:
        Velocity3.x = -1 * MovementSpeed;
        break;
    case RIGHT:
        Velocity3.x =  MovementSpeed;
        break;
    case DOWN:
        Velocity3.y =  MovementSpeed;
        break;
    case UP:
        Velocity3.y = -1 * MovementSpeed;
        break;

    case NOT_LEFT:
        Velocity3.x = 0;
        break;
    case NOT_RIGHT:
        Velocity3.x = 0;
        break;
    case NOT_UP:
        Velocity3.y = 0;
        break;
    case NOT_DOWN:
        Velocity3.y = 0;
        break;
    }
}
void Unit::UpdatePosition3()
{
    sf::Vector2f start;
    //if(Collision==Circle) start = CircleCenter;

    if(Velocity3.x == 0 && Velocity3.y == 0 )
        return;
    float startingX = Position.x;
    float startingY = Position.y;

    Position.x+=Velocity3.x;
    Position.y+=Velocity3.y;
    //CircleCenter.x+=Velocity3.x;
    //CircleCenter.y+=Velocity3.y;

    if(CheckForCollisions())
    {
        Position = sf::Vector2f(startingX,startingY);
        //if(Collision==Circle) CircleCenter = start;
    }

    rect.setPosition(Position);

}
Unit::~Unit()
{
    //dtor
}
