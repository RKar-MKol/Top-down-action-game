#include "Object.h"
//////////////////////////////////////////////////////
//													//
//													//
//													//
//                 FUNKCJE KOLIZJI					//
//													//
//													//
//													//
//////////////////////////////////////////////////////

bool CollisionPointPoint(Object o1, Object o2) //RACZEJ OK
{
	if(o1.Position.x + Block_x < o2.Position.x) return 0;
	if(o1.Position.x  > o2.Position.x + Block_x) return 0;
	if(o1.Position.y + Block_y < o2.Position.y) return 0;
	if(o1.Position.y  > o2.Position.y + Block_y) return 0;

	return 1;
}
bool CollisionPointCircle(Object o1, Object o2) ///MOŻE BYC DO ZMIAN
{
	//Sprawdzamy najpierw czy jest sens dogłębnie badać kolizję każdego prostokąta z naszym punktem
	if(o1.Position.x + Block_x < o2.Position.x) return 0;
	if(o1.Position.x  > o2.Position.x + Block_x * o2.CollisionCircleRadius * 2) return 0;
	if(o1.Position.y + Block_y < o2.Position.y) return 0;
	if(o1.Position.y  > o2.Position.y + Block_y * o2.CollisionCircleRadius * 2) return 0;

	bool collision = false;
	for(int i = 0;i < o2.Blocks.size(); i++)
	{
		if( (o1.Position.x + Block_x >= o2.Blocks[i]->position.x) &&
			(o1.Position.x  <= o2.Blocks[i]->position.x + Block_x) &&
			(o1.Position.y + Block_y >= o2.Blocks[i]->position.y) &&
			(o1.Position.y  <= o2.Blocks[i]->position.y + Block_y)
		  ) collision = true;
		if(collision) return 1;
	}
	return 0;
}
bool CollisionPointRect(Object o1, Object o2) //RACZEJ OK
{
	if(o1.Position.x + Block_x < o2.Position.x) return 0;
	if(o1.Position.x  > o2.Position.x + Block_x * o2.CollisionRectSize.x) return 0;
	if(o1.Position.y + Block_y < o2.Position.y) return 0;
	if(o1.Position.y  > o2.Position.y + Block_y * o2.CollisionRectSize.y) return 0;

	return 1;
}
bool CollisionPointArc(Object o1, Object o2){return 1;} //NIE SKONCZONE
bool CollisionCircleCircle(Object o1, Object o2) ///MOŻE BYC DO ZMIAN + NIE SKONCZONE
{
	if(o1.Position.x + Block_x * o1.CollisionCircleRadius * 2 < o2.Position.x) return 0;
	if(o1.Position.x  > o2.Position.x + Block_x * o2.CollisionCircleRadius * 2) return 0;
	if(o1.Position.y + Block_y * o1.CollisionCircleRadius * 2 < o2.Position.y) return 0;
	if(o1.Position.y  > o2.Position.y + Block_y * o2.CollisionCircleRadius * 2) return 0;

	sf::Vector2f RoznicaWektor = o1.CollisionCircleCenter - o2.CollisionCircleCenter;
	float RoznicaDlugosc = sqrt(RoznicaWektor.x*RoznicaWektor.x + RoznicaWektor.y*RoznicaWektor.y);
	float min =  Block_x;
	if(min > Block_y) min = Block_y;
	if(RoznicaDlugosc<=o1.CollisionCircleRadius * min + o2.CollisionCircleRadius * min) return 1;

}
bool CollisionCircleRect(Object o1, Object o2) //NIE SKONCZONE
{
	//NIE DOKOŃCZONE
	//if(CollisionPointRect(Center1,Position2,Size2))
		return 1;



}
bool CollisionCircleArc(Object o1, Object o2){return 1;}//NIE SKONCZONE
bool CollisionRectRect(Object o1, Object o2) // RACZEJ OK
{
	if(o1.Position.x + o1.CollisionRectSize.x < o2.Position.x) return 0;
	if(o1.Position.x  > o2.Position.x + o2.CollisionRectSize.x) return 0;
	if(o1.Position.y + o1.CollisionRectSize.y < o2.Position.y) return 0;
	if(o1.Position.y  > o2.Position.y + o2.CollisionRectSize.y) return 0;

	return 1;
}
bool CollisionRectArc(Object o1, Object o2){return 1;}//NIE SKONCZONE
bool CollisionArcArc(Object o1, Object o2){return 1;}//NIE SKONCZONE

bool Object::CollisionCheckWithAnotherObject(Object& Objekt) //JEŚLI 1 TO JEST KOLIZJA
	{
		switch(this->Collision)
		{
		case Point:
			if(Objekt.Collision==Point)
				return CollisionPointPoint(*this,Objekt);
			if(Objekt.Collision==Circle)
				return CollisionPointCircle(*this,Objekt);
			if(Objekt.Collision==Rectangle)
				return CollisionPointRect(*this,Objekt);
			if(Objekt.Collision==Arc)
				return CollisionPointArc(*this,Objekt);
			//EWENTUALNY RAPORT O BŁĘDACH
			return 0; // return 0 jest tutaj w razie nieprzewidzianego typu kolizji
			break;    // objektu Objekt, wtedy uznawany jest brak kolizji.
					  // Tak samo w poniższych przypadkach.
		case Rectangle:
			if(Objekt.Collision==Point)
				return CollisionPointRect(Objekt,*this);
			if(Objekt.Collision==Circle)
				return CollisionCircleRect(Objekt,*this);
			if(Objekt.Collision==Rectangle)
				return CollisionRectRect(*this,Objekt);
			if(Objekt.Collision==Arc)
				return CollisionRectArc(*this,Objekt);
			//EWENTUALNY RAPORT O BŁĘDACH
			return 0;
			break;
		case Circle:
			if(Objekt.Collision==Point)
				return CollisionPointCircle(Objekt,*this);
			if(Objekt.Collision==Circle)
				return CollisionCircleCircle(*this,Objekt);
			if(Objekt.Collision==Rectangle)
				return CollisionCircleRect(*this,Objekt);
			if(Objekt.Collision==Arc)
				return CollisionCircleArc(*this,Objekt);
			//EWENTUALNY RAPORT O BŁĘDACH
			return 0;
			break;
		case Arc: //ARC DO ZROBIENIA
			if(Objekt.Collision==Point)
				return CollisionPointArc(Objekt,*this);
			if(Objekt.Collision==Circle)
				return CollisionCircleArc(Objekt,*this);
			if(Objekt.Collision==Rectangle)
				return CollisionRectArc(Objekt,*this);
			if(Objekt.Collision==Arc)
				return CollisionArcArc(*this,Objekt);
			//EWENTUALNY RAPORT O BŁĘDACH
			return 0;
			break;
		default:
			//EWENTUALNY RAPORT O BŁĘDACH
			return 0;// return 0 jest tutaj w razie nieprzewidzianego typu kolizji
		}			 // objektu this, wtedy uznawany jest brak kolizji.
	}

//////////////////////////////////////////////////////
//													//
//													//
//													//
//                 KONSTRUKTORY						//
//													//
//													//
//													//
//////////////////////////////////////////////////////

Object::Object(sf::Vector2f pos) //konstruktor punktu
{
	Collision = Point;
	Position = pos;
	CollisionBlock* tmp = new CollisionBlock(pos);
	Blocks.push_back(tmp);
}
Object::Object(sf::Vector2f pos, sf::Vector2f size) //konstruktor prostokata
{
	if(!(size.x > 0 && size.y > 0)) return;
	Collision = Rectangle;
	Position = pos;
	CollisionRectSize = size;

	CollisionBlock* tmp;
	for(int i = 0 ; i < size.x ; i++)
		for(int j = 0 ; j < size.y ; j++)
		{
			tmp = new CollisionBlock( pos + sf::Vector2f(i * Block_x, j * Block_y) );
			Blocks.push_back(tmp);
		}
}
Object::Object(sf::Vector2f pos, float radius) //konstruktor okregu NIE SKONCZONY
{
	Collision = Circle;
	Position = pos;
	CollisionCircleRadius = radius;
	// trzeba bedzie obliczyc circle center
}
Object::Object(sf::Vector2f pos, float radius, float angle) //konstruktor łuku NIE SKONCZONY
{
	Collision = Arc;
	Position = pos;
	CollisionArcRadius = radius;
	CollisionArcAngle = angle;
}

Object::~Object()//destruktor
{
	if(!(Blocks.size()>=1)) return;
	for(int i = Blocks.size()-1;i>=0;--i)
		delete Blocks[i];
}
