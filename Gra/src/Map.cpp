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
    //ctor
}

Map::~Map()
{
    //dtor
}
