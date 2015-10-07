//#include <SFML\Graphics.hpp>
//#include <cmath>
#include "Object.h"
#include "Map.h"

#define ScreenHeight 640
#define ScreenWidth 800

using namespace std;

sf::RenderWindow GameWindow;
sf::View Camera;
void CameraUpdate(Object*WzgledemKtoregoCamera, Map* mapa);

int main()
{
    //@@@@@@@@@@@@@@@@@@@//
    //     T E S T Y     //
    //@@@@@@@@@@@@@@@@@@@//


    //@@@@@@@@@@@@@@@@@@@//
    //     T E S T Y     //
    //@@@@@@@@@@@@@@@@@@@//

    /** TESTOWANIE RAFAL **/
    sf::View Camera;


    Object*postac = new Object(sf::Vector2f(50,50),30);



    Map*testowa_mapa = new Map;
    testowa_mapa->LoadMapFromFile("test.csv");
    testowa_mapa->DisplayMapOfCollisions();
    testowa_mapa->CreateMapFromArray();


    //cout << testowa_mapa->MapSize.x  << "   " << testowa_mapa->MapSize.y << endl;
    /** TESTOWANIE RAFAL **/


    sf::RenderWindow GameWindow( sf::VideoMode(ScreenWidth,ScreenHeight), "Game" ,sf::Style::Default);
    sf::Clock clock;

    /** %%%%%%%%%%%%%%%%% GAME LOOP  %%%%%%%%%%%%%%%%% **/
    while( GameWindow.isOpen() )
    {
        sf::Event event;
        while( GameWindow.pollEvent( event ) )
        {
            if( event.type == sf::Event::Closed )
                 GameWindow.close();

        }
        GameWindow.clear();


        GameWindow.draw(*testowa_mapa);
        GameWindow.draw(*postac);

        GameWindow.display();
    }
    /** %%%%%%%%%%%%%%%%% GAME LOOP  %%%%%%%%%%%%%%%%% **/

}
void CameraUpdate(Object*WzgledemKtoregoCamera, Map* mapa)
{





    float tempX = WzgledemKtoregoCamera->Position.x; //
    float tempY = WzgledemKtoregoCamera->Position.y;
    sf::Vector2f temporary_vector(Camera.getCenter()); // PRZY FULL SCREENIE SIE JEBIE

    float MapSizeX = mapa->MapSize.x;
    float MapSizeY = mapa->MapSize.y;




    if(tempX >= ScreenWidth/2 && MapSizeX > tempX + ScreenWidth/2)
        temporary_vector.x = tempX;
    else
    {
        if(MapSizeX >= ScreenWidth)
        {

            if(tempX < ScreenWidth/2)
                temporary_vector.x = ScreenWidth/2;
            if(MapSizeX <= tempX + ScreenWidth/2)
                temporary_vector.x = MapSizeX - ScreenWidth/2;
        }
    }

    if(tempY >= ScreenHeight/2 && MapSizeY > tempY + ScreenHeight/2)
        temporary_vector.y = tempY;
    else
    {
        if(MapSizeY >= ScreenHeight)
        {

            if(tempY < ScreenHeight/2)
                temporary_vector.y = ScreenHeight/2;
            if(MapSizeY<= tempY + ScreenHeight/2)
                temporary_vector.y = MapSizeY - ScreenHeight/2;
        }

    }
    Camera.setCenter(temporary_vector);
    GameWindow.setView(Camera);



}
