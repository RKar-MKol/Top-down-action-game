#include <SFML\Graphics.hpp>
#include <math.h>
#include <vector>


using namespace std;

//STAŁE DEFINIUNIUJĄCE WYMIARY JEDNEGO PUNKTU KOLIZJI
const float Block_x = 10;
const float Block_y = 10;

class Object;


// Kolizja oparta na blockach kolizji (prostokąty o tej samej wielkości).
// Jedna grupa prostokątów opisuje kolizję jednego obiektu).
struct CollisionBlock
{
	sf::Vector2f position;
	sf::Vector2f size;
	CollisionBlock()
	{
		size = sf::Vector2f(Block_x,Block_y);
	}
	CollisionBlock(sf::Vector2f pos)
	{
		position = pos;
		size = sf::Vector2f(Block_x,Block_y);
	}
};
/*----------------------------------------------------
|	Problemy z kolizją:
|	----------------------------------------------
|	Niesprecyzowany model kolizji Circle i Arc
|	Wymyśliłem 3 możliwe modele kolizji Circle
|	i 2 możliwe modele kolizji Arc.
|
|	Bez sprecyzowania jakiego modelu się użyje,
|	nie ma sensu implementować kolizji, chyba że
|	zaimplementuję kolizję każdego prostokąta
|	jednego obiektu z każdym prostokątem
|	drugiego obiektu, co jest mało wydajne.
|	W innym przypadku będzie trzeba pisać
|	funkcję kolizji od nowa.
|	--------------------------------------------------
*/
//FUNKCJE DO KOLIZJI
bool CollisionPointPoint(Object o1, Object o2); //OK
bool CollisionPointCircle(Object o1, Object o2); //Raczej OK
bool CollisionPointRect(Object o1, Object o2);//OK
bool CollisionPointArc(Object o1, Object o2); //NIE SKONCZONE
bool CollisionCircleCircle(Object o1, Object o2);//NIE SKONCZONE
bool CollisionCircleRect(Object o1, Object o2);//NIE SKONCZONE
bool CollisionCircleArc(Object o1, Object o2);//NIE SKONCZONE
bool CollisionRectRect(Object o1, Object o2);//OK
bool CollisionRectArc(Object o1, Object o2);//NIE SKONCZONE
bool CollisionArcArc(Object o1, Object o2);//NIE SKONCZONE


enum CollisionType
	{
		Point, Circle, Rectangle, Arc, END
	};
class Object
{
	//POLA KLASY
	sf::Vector2f Position;

	//POLA DOTYCZĄCE KOLIZJI
	CollisionType Collision;
	vector<CollisionBlock*> Blocks;
	sf::Vector2f CollisionRectSize;
	sf::Vector2f CollisionCircleCenter;
	float CollisionCircleRadius;
	float CollisionArcRadius;
	float CollisionArcAngle;

	//METODY
	bool CollisionCheckWithAnotherObject(Object& Objekt); //JEŚLI 1 TO JEST KOLIZJA

public:

	//KONSTRUKTORY + DESTRUKTOR
	Object(sf::Vector2f pos); //konstruktor punktu
	Object(sf::Vector2f pos, sf::Vector2f size); //konstruktor prostokata
	Object(sf::Vector2f pos, float radius); //konstruktor okregu
	Object(sf::Vector2f pos, float radius, float angle); //konstruktor łuku

	~Object(); //destruktor NIE WIEM CZY WYSTARCZY MOJ SPOSOB CZYSZCZENIA PAMIECI

	//FUNKCJE ZAPRZYJAŹNIONE

	friend bool CollisionPointPoint(Object o1, Object o2);
	friend bool CollisionPointCircle(Object o1, Object o2);
	friend bool CollisionPointRect(Object o1, Object o2);
	friend bool CollisionPointArc(Object o1, Object o2);
	friend bool CollisionCircleCircle(Object o1, Object o2);
	friend bool CollisionCircleRect(Object o1, Object o2);
	friend bool CollisionCircleArc(Object o1, Object o2);
	friend bool CollisionRectRect(Object o1, Object o2);
	friend bool CollisionRectArc(Object o1, Object o2);
	friend bool CollisionArcArc(Object o1, Object o2);

};
