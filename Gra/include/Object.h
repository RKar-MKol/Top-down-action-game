#pragma once
#include <SFML\Graphics.hpp>
#include <math.h>
#include <vector>
#include <iostream>
#include "Graphic_Engine.h"


const float Block_x = 10; //JESLI Block_x != Block_y nalezy zmienic kolizje circlepoint
const float Block_y = 10;

class Object;


//MATEMATYKA
static float Vector2fDistance(sf::Vector2f Point1, sf::Vector2f Point2)
{return sqrt( (Point1.x-Point2.x)*(Point1.x-Point2.x)+(Point1.y-Point2.y)*(Point1.y-Point2.y) );}

//FUNKCJE DO KOLIZJI
bool operator==(Object& o1, Object& o2);
//operator == jest definiowany po to aby oszczedzic na czasie
//przy jego uzywaniu. Porownywanie porownuje tylko ID.
bool CollisionPointPoint(Object& o1, Object& o2);
bool CollisionPointCircle(Object& o1, Object& o2);
bool CollisionPointRect(Object& o1, Object& o2);
bool CollisionCircleCircle(Object& o1, Object& o2);
bool CollisionCircleRect(Object& o1, Object& o2);
bool CollisionRectRect(Object& o1, Object& o2);

enum CollisionShape
	{
		Point, Circle, Rectangle, END
	};

class Object : public sf::Drawable
{
    //ID Obiektow
public:  static int IDiterator;
         static vector<Object*> AllObjects;
         sf::Vector2f Position;
protected: int ID;
	//POLA KLASY

	CollisionShape Collision;
	sf::Vector2f RectSize;
	float CircleRadius;
	sf::RectangleShape rect;


	//METODY
	bool CollisionCheckWithAnotherObject(Object& Obj); //JEŚLI 1 TO JEST KOLIZJA
public:
    bool CheckForCollisions(vector<Object*> Objs = AllObjects); //Sprawdza czy jest kolizja z grupa obiektow
                                                  //Jesli nie bylo z zadnym zwraca false
                                                  //Jesli z jakims byla zwraca true
                                                  //Z kazdym obiektem z ktorym jest kolizja wywoluje
                                                  //reakcje (np. strzaly wywoluja otrzymanie obrazen itp.)
                                                  //reakcja mogłaby być klasą

    //Potem to bedzie protected ale na razie testy
    //void Move(sf::Vector2f Offset) {Position+=Offset;}
   // void ChangePosition(sf::Vector2f Position) {this->Position = Position;}

    //DRAW
    virtual void draw(sf::RenderTarget& target,sf::RenderStates states=sf::RenderStates::Default) const;

	//KONSTRUKTORY + DESTRUKTOR
	Object(sf::Vector2f pos); //konstruktor punktu
	Object(sf::Vector2f pos, sf::Vector2f size); //konstruktor prostokata
	Object(sf::Vector2f pos, float radius); //konstruktor okregu

	//~Object(); //destruktor NIE WIEM CZY POTRZEBNY

	//FUNKCJE ZAPRZYJAŹNIONE
    friend bool operator==(Object& o1, Object& o2);
	friend bool CollisionPointPoint(Object& o1, Object& o2);
	friend bool CollisionPointCircle(Object& o1, Object& o2);
	friend bool CollisionPointRect(Object& o1, Object& o2);
	friend bool CollisionCircleCircle(Object& o1, Object& o2);
	friend bool CollisionCircleRect(Object& o1, Object& o2);
	friend bool CollisionRectRect(Object& o1, Object& o2);
};
