//#include <SFML\Graphics.hpp>
//#include <cmath>
#include "Object.h"
#include "Map.h"

#define ScreenHeight 640
#define ScreenWidth 800

using namespace std;


int main()
{
    //@@@@@@@@@@@@@@@@@@@//
    //     T E S T Y     //
    //@@@@@@@@@@@@@@@@@@@//


    //@@@@@@@@@@@@@@@@@@@//
    //     T E S T Y     //
    //@@@@@@@@@@@@@@@@@@@//

    /** TESTOWANIE RAFAL **/
    Map*testowa_mapa = new Map;
    testowa_mapa->LoadMapFromFile("test.csv");
    testowa_mapa->DisplayMapOfCollisions();
    testowa_mapa->CreateMapFromArray();

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


        GameWindow.display();
    }
    /** %%%%%%%%%%%%%%%%% GAME LOOP  %%%%%%%%%%%%%%%%% **/

}

