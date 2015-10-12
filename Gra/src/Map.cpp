#include "Map.h"



void Map::LoadMapFromFile(string path)
{
    /**if(!graphic.loadFromFile(string("Graphic/") + path + ".png"));
    {
        cout << "COS SIE NIE WCZYTALO DO CHUJA w konstruktorze mapy" << endl;
    }

    sprite.setTexture(graphic);
    **/

    // OBSLUGA PLIKU .CSV
    vector <vector <int> > temporary_vector2d;

    ifstream plik;
    //string m = "Maps/" + path +  ".csv";
    string m =  path;
    plik.open(m.c_str());

    while(!plik.eof())
    {
        string buffer;
        getline(plik,buffer);
        stringstream przetwarzanie_wiersza(buffer);


        vector <int> temporary;
        while(!przetwarzanie_wiersza.eof())
        {
            int liczba;
            char przecinek;
            przetwarzanie_wiersza >> liczba >> przecinek;
            temporary.push_back(liczba);
            //cout << liczba << " ";
        }
        if(temporary.size() != 1)
            temporary_vector2d.push_back(temporary); // problem z bufferem

       //cout << endl;

    }


    // TRANSPONUJEMY
    for(int i = 0; i<temporary_vector2d[0].size(); i++)
    {
        vector <int> temp;
        for(int j = 0; j< temporary_vector2d.size(); j++)
            temp.push_back(temporary_vector2d[j][i]); //transponowane !

        MapOfCollisions.push_back(temp);
    }

    MapSize.x = TileSize.x * MapOfCollisions.size();
    MapSize.y = TileSize.y * MapOfCollisions[0].size();

}
void Map::CreateMapFromArray()
{
    for(unsigned int i = 0;i<MapOfCollisions[i].size();i++)
    {
        int Poczatek = -1;

        for(unsigned int j = 0; j< MapOfCollisions.size(); j++)
        {
            if(MapOfCollisions[j][i] != -1 && Poczatek == -1)
                Poczatek = j;
            if(MapOfCollisions[j][i] == -1 && Poczatek != -1)
            {
                ObjectsOnMap.push_back(new Object(sf::Vector2f(TileSize.x * Poczatek,TileSize.y * i),
                                                  sf::Vector2f( (j- Poczatek) * TileSize.x,TileSize.y)));
                Poczatek = -1;
            }
        }
        if(Poczatek != -1)
        {
            ObjectsOnMap.push_back(new Object(sf::Vector2f(TileSize.x * Poczatek,TileSize.y * i),
                                              sf::Vector2f( (MapOfCollisions.size()- Poczatek) * TileSize.x,TileSize.y)));
            Poczatek = -1;
        }

    }
}
void Map::DisplayMapOfCollisions()
{
    cout << endl;
    for(unsigned int i = 0;i<MapOfCollisions[i].size();i++)
    {

        for(int j = 0; j< MapOfCollisions.size(); j++)
            cout << MapOfCollisions[j][i]<< " ";
        cout << endl;
    }
}
Map::Map()
{

}

Map::~Map()
{
    //dtor
}
void Map::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    for(unsigned int i = 0;i<ObjectsOnMap.size();i++)
        target.draw(*ObjectsOnMap[i]);
}
