#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include "Object.h"

using namespace std;

const sf::Vector2f TileSize(32.0f,32.0f);

class Map : public sf::Drawable
{
private:
    vector < vector <int> > MapOfCollisions;
    vector <Object*> ObjectsOnMap;
public:
    void LoadMapFromFile(string PathToFile); // wczytuje liczby z .csv do MapOfCollisions
    void CreateMapFromArray(); // tworzy mape z MapOfCollisions

    Map();
    virtual ~Map();

    //DRAW
    virtual void draw(sf::RenderTarget& target,sf::RenderStates states=sf::RenderStates::Default) const;

    /** TESTY **/
    void DisplayMapOfCollisions();

};

#endif // MAP_H
