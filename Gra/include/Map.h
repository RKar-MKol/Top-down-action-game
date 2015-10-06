#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
//#include "Object.h"

using namespace std;

class Map
{
private:
    vector < vector <int> > MapOfCollisions;
public:
    void LoadMapFromFile(string PathToFile); // wczytuje liczby z .csv do MapOfCollisions

    Map();
    virtual ~Map();

    /** TESTY **/
    void DisplayMapOfCollisions();

};

#endif // MAP_H
