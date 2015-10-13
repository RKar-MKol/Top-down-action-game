#ifndef UNIT_H
#define UNIT_H

#include <Object.h>

enum Direction{LEFT,RIGHT,DOWN,UP};

class Unit : public Object
{
    public:
        Unit(sf::Vector2f Position,float radius);

        void MovePLS();
        sf::Vector2f GetRotation() {return Rotation;}
        void SetRotation(sf::Vector2f Rotation) {this->Rotation = Rotation;}
        void SetTexture(sf::Texture *texture);

        //DRAW
        virtual void draw(sf::RenderTarget& target,sf::RenderStates states=sf::RenderStates::Default) const;

        ~Unit();

    private:
        // testowa textura
        sf::Texture testowa_textura;

        // sprite
        sf::Sprite sprite;

        //Velocity odpowiada za przesuniecie
        sf::Vector2f Velocity;
        //Rotation to wektor jednostkowy oznaczający kierunek
        sf::Vector2f Rotation;
        float MovementSpeed;


};

#endif // UNIT_H
