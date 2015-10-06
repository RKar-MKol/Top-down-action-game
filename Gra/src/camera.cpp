void UpdateCamera()
{



    float tempX = ActualCharacter->Position.x * ActualMap->TileSize.x; //
    float tempY = ActualCharacter->Position.y * ActualMap->TileSize.y;
    sf::Vector2f temporary_vector(Camera.getCenter()); /** PRZY FULL SCREENIE SIE JEBIE **/

    float MapSizeX = ActualMap->graphic.getSize().x;
    float MapSizeY = ActualMap->graphic.getSize().y;

    float ScreenWidth = GameWindow->getSize().x;
    float ScreenHeight = GameWindow->getSize().y;


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
    GameWindow->setView(Camera);


}
