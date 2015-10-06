//#include <SFML\Graphics.hpp>
//#include <cmath>
#include "Object.h"
#include "Map.h"

int main()
{
    //@@@@@@@@@@@@@@@@@@@//
    //     T E S T Y     //
    //@@@@@@@@@@@@@@@@@@@//
    std::vector<Object*> Objects;
    Object* Prostokat1 = new Object(sf::Vector2f(50,50),sf::Vector2f(100,100));
    Objects.push_back(Prostokat1);
    Object* Prostokat2 = new Object(sf::Vector2f(50,201),sf::Vector2f(50,200));
    Objects.push_back(Prostokat2);

    Object* Okrag = new Object(sf::Vector2f(50,50),25);
    Objects.push_back(Okrag);


    /*Object* Okrag1 = new Object(sf::Vector2f(0,0),25);
    Objects.push_back(Okrag1);
    Object* Okrag2 = new Object(sf::Vector2f(50,0),25);
    Objects.push_back(Okrag2);
    Object* Okrag3 = new Object(sf::Vector2f(100,0),25);
    Objects.push_back(Okrag3);
    Object* Okrag4 = new Object(sf::Vector2f(150,0),25);
    Objects.push_back(Okrag4);
    Object* Okrag5 = new Object(sf::Vector2f(0,50),25);
    Objects.push_back(Okrag5);
    Object* Okrag6 = new Object(sf::Vector2f(150,50),25);
    Objects.push_back(Okrag6);
    Object* Okrag7 = new Object(sf::Vector2f(0,100),25);
    Objects.push_back(Okrag7);
    Object* Okrag8 = new Object(sf::Vector2f(50,100),25);
    Objects.push_back(Okrag8);
    Object* Okrag9 = new Object(sf::Vector2f(100,100),25);
    Objects.push_back(Okrag9);
    Object* Okrag10 = new Object(sf::Vector2f(150,100),25);
    Objects.push_back(Okrag10);

    Object* Okrag11 = new Object(sf::Vector2f(50,50),25);
    Objects.push_back(Okrag11);
    Object* Okrag12 = new Object(sf::Vector2f(100,50),25);
    Objects.push_back(Okrag12);*/

   // if(Prostokat1->CheckForCollisions(Objects)) std::cout<<"\napapapa";
    //if(Prostokat2->CheckForCollisions(Objects)) std::cout<<"\napapapa";

    /** TESTOWANIE RAFAL **/
    Map*testowa_mapa = new Map;
    testowa_mapa->LoadMapFromFile("test.csv");
    testowa_mapa->DisplayMapOfCollisions();

    /** TESTOWANIE RAFAL **/


    sf::RenderWindow okno( sf::VideoMode( 800, 800 ), "Kurs SFML 2.0 - http://cpp0x.pl" );
    sf::Clock stoper;
    while( okno.isOpen() )
    {
        sf::Event event;
        while( okno.pollEvent( event ) )
        {
            if( event.type == sf::Event::Closed )
                 okno.close();

        } //while
        okno.clear();

        for(int i=0;i<Objects.size();i++)
            Objects[i]->draw(okno);

        okno.display();
    } //while
    return 0;
}

