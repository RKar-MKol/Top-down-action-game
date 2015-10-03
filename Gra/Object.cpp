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

bool CollisionPointPoint(Object o1, Object o2)
{
	if(o1.Position.x + Block_x < o2.Position.x) return 0;
	if(o1.Position.x  > o2.Position.x + Block_x) return 0;
	if(o1.Position.y + Block_y < o2.Position.y) return 0;
	if(o1.Position.y  > o2.Position.y + Block_y) return 0;
	return 1;
}
bool CollisionPointCircle(Object o1, Object o2)
{
    //Kolizja nie jest perfect, jest przyblizona
    float MAXdist = o2.CircleRadius + sqrt(Block_x)/2;
    float MINdist = o2.CircleRadius + Block_x/2;
    float Avg = (MAXdist + MINdist) / 2;
    if(Vector2fDistance(o1.Position+sf::Vector2f(Block_x/2,Block_x/2),o2.CircleCenter) > Avg) return 0;
    return 1;
}
bool CollisionPointRect(Object o1, Object o2)
{
	if(o1.Position.x + Block_x < o2.Position.x) return 0;
	if(o1.Position.x  > o2.Position.x + o2.RectSize.x) return 0;
	if(o1.Position.y + Block_y < o2.Position.y) return 0;
	if(o1.Position.y  > o2.Position.y + o2.RectSize.y) return 0;

	return 1;
}
bool CollisionCircleCircle(Object o1, Object o2)
{
    if(o1.CircleRadius + o2.CircleRadius < Vector2fDistance(o1.CircleCenter,o2.CircleCenter)) return false;
    return true;
}
bool CollisionCircleRect(Object o1, Object o2)
{
	if(o2.Position.y + o2.RectSize.y < o1.Position.y) return 0;
	if(o2.Position.y > o1.Position.y + 2*o1.CircleRadius) return 0;
	if(o2.Position.x + o2.RectSize.x < o1.Position.x) return 0;
	if(o2.Position.x > o1.Position.x + 2*o1.CircleRadius) return 0;

	if(o1.CircleCenter.x < o2.RectSize.x + o2.Position.x && o1.CircleCenter.x > o2.Position.x) return 1;
	if(o1.CircleCenter.y < o2.RectSize.y + o2.Position.y && o1.CircleCenter.y > o2.Position.y) return 1;

	sf::Vector2f TMPPoint = o2.Position;
	if(Vector2fDistance(TMPPoint,o1.CircleCenter) > o1.CircleRadius) return 0;
	TMPPoint = o2.Position + sf::Vector2f(0,o2.RectSize.y);
	if(Vector2fDistance(TMPPoint,o1.CircleCenter) > o1.CircleRadius) return 0;
	TMPPoint = o2.Position + sf::Vector2f(o2.RectSize.x,0);
	if(Vector2fDistance(TMPPoint,o1.CircleCenter) > o1.CircleRadius) return 0;
	TMPPoint = o2.Position + o2.RectSize;
	if(Vector2fDistance(TMPPoint,o1.CircleCenter) > o1.CircleRadius) return 0;

	return 1;
}
bool CollisionRectRect(Object o1, Object o2) // RACZEJ OK
{
	if(o1.Position.x + o1.RectSize.x < o2.Position.x) return 0;
	if(o1.Position.x  > o2.Position.x + o2.RectSize.x) return 0;
	if(o1.Position.y + o1.RectSize.y < o2.Position.y) return 0;
	if(o1.Position.y  > o2.Position.y + o2.RectSize.y) return 0;

	return 1;
}
bool Object::CheckForCollisions(std::vector<Object> Objs)
{
    bool ThereIsCollision = false;
    for(int i=0;i<Objs.size();i++)
    {
        if(CollisionCheckWithAnotherObject(Objs[i]))
           {
               //REAKCJA NA KOLIZJE


               ThereIsCollision = true;
           }
    }

    if(ThereIsCollision) return 1;
    return 0;
}
bool Object::CollisionCheckWithAnotherObject(Object& Obj) //JEŚLI 1 TO JEST KOLIZJA
	{
		switch(this->Collision)
		{
		case Point:
			if(Obj.Collision==Point)
				return CollisionPointPoint(*this,Obj);
			if(Obj.Collision==Circle)
				return CollisionPointCircle(*this,Obj);
			if(Obj.Collision==Rectangle)
				return CollisionPointRect(*this,Obj);
			//EWENTUALNY RAPORT O BŁĘDACH
			return 0; // return 0 jest tutaj w razie nieprzewidzianego typu kolizji
			break;    // objektu ekt, wtedy uznawany jest brak kolizji.
					  // Tak samo w poniższych przyp(Point1.x-Point2.x)*(Point1.x-Point2.x)adkach.
		case Rectangle:
			if(Obj.Collision==Point)
				return CollisionPointRect(Obj,*this);
			if(Obj.Collision==Circle)
				return CollisionCircleRect(Obj,*this);
			if(Obj.Collision==Rectangle)
				return CollisionRectRect(*this,Obj);
			//EWENTUALNY RAPORT O BŁĘDACH
			return 0;
			break;
		case Circle:
			if(Obj.Collision==Point)
				return CollisionPointCircle(Obj,*this);
			if(Obj.Collision==Circle)
				return CollisionCircleCircle(*this,Obj);
			if(Obj.Collision==Rectangle)
				return CollisionCircleRect(*this,Obj);
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
}
Object::Object(sf::Vector2f pos, sf::Vector2f size) //konstruktor prostokata
{
	Collision = Rectangle;
	Position = pos;
	RectSize = size;
}
Object::Object(sf::Vector2f pos, float radius) //konstruktor okregu NIE SKONCZONY
{
	Collision = Circle;
	Position = pos;
	CircleRadius = radius;
	CircleCenter = pos + sf::Vector2f(radius,radius);
	// trzeba bedzie obliczyc circle center
}

Object::~Object()//destruktor
{

}
