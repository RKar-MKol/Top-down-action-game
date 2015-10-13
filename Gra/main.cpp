
#include <time.h>

#include "Unit.h"
#include "Map.h"

#define ScreenHeight 640
#define ScreenWidth 800

#define FPS 60.0
using namespace std;


void CameraUpdate(Object*WzgledemKtoregoCamera, Map* mapa,sf::View* Cam,sf::RenderWindow *Gw);
sf::Vector2f RealMousePosition(sf::RenderWindow *Gw);

int main()
{
    srand(time(NULL));

    sf::RenderWindow GameWindow( sf::VideoMode(ScreenWidth,ScreenHeight), "Game" ,sf::Style::Default);
    sf::View Camera = GameWindow.getDefaultView();

    GameWindow.setKeyRepeatEnabled(true);

    sf::Clock clock;
    sf::Time TimePerFrame = sf::seconds(1/FPS);


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


    /** TESTOWANIE RAFAL **/





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
            case sf::Event::MouseMoved:
                postac->Rotate(RealMousePosition(&GameWindow));
                break;



            }
        }
        //Reakcja
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
sf::Vector2f RealMousePosition(sf::RenderWindow *GW)
{
    sf::Vector2f SrodekEkranu = GW->getView().getCenter();
    sf::Vector2f LewyGornyRogEkranu = sf::Vector2f(SrodekEkranu.x - GW->getSize().x/2,
                                                   SrodekEkranu.y - GW->getSize().y/2);
    sf::Vector2f mouse(sf::Mouse::getPosition(*GW));
    return sf::Vector2f(LewyGornyRogEkranu.x + mouse.x, LewyGornyRogEkranu.y + mouse.y);
}
