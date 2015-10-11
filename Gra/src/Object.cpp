#include "Object.h"



int Object::IDiterator = 1;
vector<Object*> Object::AllObjects;
bool operator==(Object& o1, Object& o2) {return o1.ID == o2.ID;}
//////////////////////////////////////////////////////
//													//
//													//
//													//
//                 FUNKCJE KOLIZJI					//
//													//
//													//
//													//
//////////////////////////////////////////////////////

bool CollisionPointPoint(Object& o1, Object& o2)
{
	if(o1.Position.x + Block_x < o2.Position.x) return 0;
	if(o1.Position.x  > o2.Position.x + Block_x) return 0;
	if(o1.Position.y + Block_y < o2.Position.y) return 0;
	if(o1.Position.y  > o2.Position.y + Block_y) return 0;
	return 1;
}
bool CollisionPointCircle(Object& o1, Object& o2)
{
    //Kolizja nie jest perfect, jest przyblizona
    float MAXdist = o2.CircleRadius + sqrt(Block_x)/2;
    float MINdist = o2.CircleRadius + Block_x/2;
    float Avg = (MAXdist + MINdist) / 2;
    if(Vector2fDistance(o1.Position+sf::Vector2f(Block_x/2,Block_x/2),o2.CircleCenter) > Avg) return 0;
    return 1;
}
bool CollisionPointRect(Object& o1, Object& o2)
{
	if(o1.Position.x + Block_x < o2.Position.x) return 0;
	if(o1.Position.x  > o2.Position.x + o2.RectSize.x) return 0;
	if(o1.Position.y + Block_y < o2.Position.y) return 0;
	if(o1.Position.y  > o2.Position.y + o2.RectSize.y) return 0;

	return 1;
}
bool CollisionCircleCircle(Object& o1, Object& o2)
{
    if(o1.CircleRadius + o2.CircleRadius < Vector2fDistance(o1.CircleCenter,o2.CircleCenter)) return false;
    return true;
}
bool CollisionCircleRect(Object& o1, Object& o2)
{
	if(o2.Position.y + o2.RectSize.y < o1.Position.y) return 0;
	if(o2.Position.y > o1.Position.y + 2*o1.CircleRadius) return 0;
	if(o2.Position.x + o2.RectSize.x < o1.Position.x) return 0;
	if(o2.Position.x > o1.Position.x + 2*o1.CircleRadius) return 0;

	if(o1.CircleCenter.x < o2.RectSize.x + o2.Position.x && o1.CircleCenter.x > o2.Position.x) return 1;
	if(o1.CircleCenter.y < o2.RectSize.y + o2.Position.y && o1.CircleCenter.y > o2.Position.y) return 1;

	sf::Vector2f TMPPoint = o2.Position;
	sf::Vector2f TMPPoint2 = o2.Position + sf::Vector2f(0,o2.RectSize.y);
	sf::Vector2f TMPPoint3 = o2.Position + sf::Vector2f(o2.RectSize.x,0);
	sf::Vector2f TMPPoint4 = o2.Position + o2.RectSize;

	if(
        (Vector2fDistance(TMPPoint,o1.CircleCenter) > o1.CircleRadius)
     && (Vector2fDistance(TMPPoint2,o1.CircleCenter) > o1.CircleRadius)
     && (Vector2fDistance(TMPPoint3,o1.CircleCenter) > o1.CircleRadius)
     && (Vector2fDistance(TMPPoint4,o1.CircleCenter) > o1.CircleRadius)
      )return 0;




	return 1;
}
bool CollisionRectRect(Object& o1, Object& o2) // RACZEJ OK
{
	if(o1.Position.x + o1.RectSize.x < o2.Position.x) return 0;
	if(o1.Position.x  > o2.Position.x + o2.RectSize.x) return 0;
	if(o1.Position.y + o1.RectSize.y < o2.Position.y) return 0;
	if(o1.Position.y  > o2.Position.y + o2.RectSize.y) return 0;
	return 1;
}
bool Object::CheckForCollisions(vector<Object*> Objs)
{

    for(int i=0;i<Objs.size();i++)
    {
        if(CollisionCheckWithAnotherObject(*Objs[i]) && this!= Objs[i])
           {
               //REAKCJA NA KOLIZJE



               cout<<"\nCollision with: "<<Objs[i]->ID;
               return true;
           }
    }

    return false;
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

void Object::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    // DO UZUPELNIENIA
    //target.draw("cos tam");
    target.draw(rect,states);
}
Object::Object(sf::Vector2f pos) //konstruktor punktu
{
    ID = IDiterator++;
	Collision = Point;
	Position = pos;
	AllObjects.push_back(this);
	rect.setPosition(pos);
	rect.setSize(sf::Vector2f(Block_x,Block_y));
	rect.setFillColor(sf::Color::Red);
}
Object::Object(sf::Vector2f pos, sf::Vector2f size) //konstruktor prostokata
{
    ID = IDiterator++;
	Collision = Rectangle;
	Position = pos;
	RectSize = size;
	AllObjects.push_back(this);
	rect.setPosition(pos);
	rect.setSize(size);
	rect.setFillColor(sf::Color::Blue);
}
Object::Object(sf::Vector2f pos, float radius) //konstruktor okregu NIE SKONCZONY
{
    ID = IDiterator++;
	Collision = Circle;
	Position = pos;
	CircleRadius = radius;
	CircleCenter = pos + sf::Vector2f(radius,radius);
	AllObjects.push_back(this);
	rect.setPosition(pos);
	rect.setSize(sf::Vector2f(radius*2,radius*2));
	rect.setFillColor(sf::Color::Green);
}

/*Object::~Object()//destruktor NIE WIEM CZY POTREBNY
{

}*/
//float Vector2fDistance(sf::Vector2f Point1, sf::Vector2f Point2)
//{return sqrt( (Point1.x-Point2.x)*(Point1.x-Point2.x)+(Point1.y-Point2.y)*(Point1.y-Point2.y) );}


















