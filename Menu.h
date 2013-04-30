#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Menu
{
    public:
        Menu();

        void menuDraw(sf::RenderWindow& app);

    private:
        sf::Sprite sp_menu;



};

#endif // MENU_H
