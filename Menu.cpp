#include "Menu.h"

Menu::Menu()
{
    sf::Image img;
    img.LoadFromFile("menu.bmp");
    sp_menu.SetImage(img);
    //ctor
}

void Menu::menuDraw(sf::RenderWindow& app)
{
    app.Draw(sp_menu);
}
