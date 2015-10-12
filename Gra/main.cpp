//#include <SFML\Graphics.hpp>
//#include <cmath>
#include "Unit.h"
#include "Map.h"

#define ScreenHeight 640
#define ScreenWidth 800

#define FPS 60.0
using namespace std;


void CameraUpdate(Object*WzgledemKtoregoCamera, Map* mapa,sf::View* Cam,sf::RenderWindow *Gw);

int main()
{
    //@@@@@@@@@@@@@@@@@@@//
    //     T E S T Y     //
    //@@@@@@@@@@@@@@@@@@@//


    //@@@@@@@@@@@@@@@@@@@//
    //     T E S T Y     //
    //@@@@@@@@@@@@@@@@@@@//

    /** TESTOWANIE RAFAL **/



    Unit*postac = new Unit(sf::Vector2f(400,100),30);



    Map*testowa_mapa = new Map;
    testowa_mapa->LoadMapFromFile("mapa50x50.csv");
    testowa_mapa->DisplayMapOfCollisions();
    testowa_mapa->CreateMapFromArray();


    //cout << testowa_mapa->MapSize.x  << "   " << testowa_mapa->MapSize.y << endl;
    /** TESTOWANIE RAFAL **/


    sf::RenderWindow GameWindow( sf::VideoMode(ScreenWidth,ScreenHeight), "Game" ,sf::Style::Default);
    sf::View Camera = GameWindow.getDefaultView();
    sf::Clock clock;
    sf::Time TimePerFrame = sf::seconds(1/FPS);

    GameWindow.setKeyRepeatEnabled(true);


    /** %%%%%%%%%%%%%%%%% GAME LOOP  %%%%%%%%%%%%%%%%% **/
    while( GameWindow.isOpen() )
    {
        sf::Event event;
        while( GameWindow.pollEvent( event ) )
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                GameWindow.close();
                break;
            case sf::Event::KeyPressed:
               /* if(event.key.code == sf::Keyboard::Up)
                    postac->Move(UP);
                if(event.key.code == sf::Keyboard::Down)
                    postac->Move(DOWN);
                if(event.key.code == sf::Keyboard::Left)
                    postac->Move(LEFT);
                if(event.key.code == sf::Keyboard::Right)
                    postac->Move(RIGHT);*/

                // Move2 z Velocity
                if(event.key.code == sf::Keyboard::W)
                    postac->Move2(UP);
                if(event.key.code == sf::Keyboard::S)
                    postac->Move2(DOWN);
                if(event.key.code == sf::Keyboard::A)
                    postac->Move2(LEFT);
                if(event.key.code == sf::Keyboard::D)
                    postac->Move2(RIGHT);

                //Move3 z Velocity i release
                if(event.key.code == sf::Keyboard::I)
                    postac->Move3(UP);
                if(event.key.code == sf::Keyboard::K)
                    postac->Move3(DOWN);
                if(event.key.code == sf::Keyboard::J)
                    postac->Move3(LEFT);
                if(event.key.code == sf::Keyboard::L)
                    postac->Move3(RIGHT);
                break;
            case sf::Event::KeyReleased:
                if(event.key.code == sf::Keyboard::I)
                    postac->Move3(NOT_UP);
                if(event.key.code == sf::Keyboard::K)
                    postac->Move3(NOT_DOWN);
                if(event.key.code == sf::Keyboard::J)
                    postac->Move3(NOT_LEFT);
                if(event.key.code == sf::Keyboard::L)
                    postac->Move3(NOT_RIGHT);
                break;

            }


        }
        if(sf::Keyboard::isKeyPressed( sf::Keyboard::Up ))
			postac->SetRotation(postac->GetRotation() + sf::Vector2f(0,-1));
		if(sf::Keyboard::isKeyPressed( sf::Keyboard::Down ))
			postac->SetRotation( postac->GetRotation() + sf::Vector2f(0,1));
		if(sf::Keyboard::isKeyPressed( sf::Keyboard::Left ))
			postac->SetRotation(postac->GetRotation() + sf::Vector2f(-1,0));
		if(sf::Keyboard::isKeyPressed( sf::Keyboard::Right ))
			postac->SetRotation(postac->GetRotation() + sf::Vector2f(1,0));

        if(clock.getElapsedTime()>= TimePerFrame)
        {
            postac->UpdatePosition2(); // do move z velocity
            postac->UpdatePosition3(); // do moev z velocity i release
            GameWindow.clear();

            postac->MovePLS();



            CameraUpdate(postac,testowa_mapa,&Camera,&GameWindow);
            GameWindow.draw(*testowa_mapa);
            GameWindow.draw(*postac);

            GameWindow.display();
            clock.restart();
        }
        postac->SetRotation(sf::Vector2f(0,0));
    }
    /** %%%%%%%%%%%%%%%%% GAME LOOP  %%%%%%%%%%%%%%%%% **/
}
void CameraUpdate(Object*WzgledemKtoregoCamera, Map* mapa,sf::View* Cam,sf::RenderWindow* GW)
{





    float tempX = WzgledemKtoregoCamera->Position.x; //
    float tempY = WzgledemKtoregoCamera->Position.y;
    sf::Vector2f temporary_vector(Cam->getCenter()); // PRZY FULL SCREENIE SIE JEBIE

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
    Cam->setCenter(temporary_vector);
    GW->setView(*Cam);



}
