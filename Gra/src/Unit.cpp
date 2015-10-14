#include "Unit.h"

Unit::Unit(sf::Vector2f Position,float radius) : Object(Position,radius)
{
    if(!testowa_textura.loadFromFile("graphic/hunter.png"))
    {
        cout << " nie wczyty³a sie textura hunter.png w konstruktorze Unit" << endl;
    }
    testowa_textura.setSmooth(true);
    SetTexture(&testowa_textura);

    Rotation = sf::Vector2f(0,0);
    MovementSpeed = 2.0f;
}
void Unit::SetTexture(sf::Texture *texture)
{
    sprite.setTexture(*texture);
    sprite.setOrigin((float)texture->getSize().x/2,(float)texture->getSize().y/2);
    sprite.setPosition(Position);

}
void Unit::MovePLS()
{
    //POZYCJA STARTOWA
    sf::Vector2f start = Position;

    //NORMALIZACJA WEKTORA ROTATION
    double l = sqrt(Rotation.x*Rotation.x+Rotation.y*Rotation.y);
    if(l!=0)
    {
        Rotation.x/=l;
        Rotation.y/=l;
    }
    else
    {
        Rotation.x=0;
        Rotation.y=0;
    }

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
    sprite.setPosition(Position);
}

void Unit::Rotate(sf::Vector2f MousePos)
{

   // sprite.rotate(arc);
   float VecX = MousePos.x - Position.x;
   float VecY = MousePos.y - Position.y;

   float angle = (atan2f(VecY,VecX));

   sprite.setRotation(angle * 180.0f / PI  + 90.0f);

}

void Unit::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    target.draw(sprite);
    target.draw(rect);
}
Unit::~Unit()
{
    //dtor
}
