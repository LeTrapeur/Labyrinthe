#include <iostream>
#include <SFML/Graphics.hpp>


#include "Game.h"
#include "EditMap.h"

#include "Constantes.h"


int main()
{
    // Init Fenetre
    sf::RenderWindow app(sf::VideoMode(NB_TILE_X*TILE_WIDTH, NB_TILE_Y*TILE_HEIGHT, 32), "Labyrinthe");
    app.SetFramerateLimit(60);
    app.UseVerticalSync(true);
    //Init Menu
    sf::Image img;
    img.SetSmooth(false);
    sf::Sprite menu;
    if(img.LoadFromFile("rsc/menu.bmp"))
        menu.SetImage(img);
    else
        std::cerr << "Failed openning menu.bmp" << std::endl;
    // Init Game
    Game *game(0);
    game = new Game(app);
    // Init Editeur
    EditMap *editMap(0);
    editMap = new EditMap(app,NB_TILE_X,NB_TILE_Y,TILE_WIDTH,TILE_HEIGHT);
    // Boucle principale
    std::cout << "Application starting" << std::endl;
    // Init Mode de l'application (pour pallier aux pbs de la boucle évents)
    enum Mode{DEF, GAME, EDIT};
    Mode myMode(DEF);
    while (app.IsOpened())
    {
        sf::Event event;

        while (app.GetEvent(event))
        {
            switch(event.Type)
            {
                case sf::Event::Closed :
                app.Close();
                break;
                case sf::Event::KeyPressed :
                switch(event.Key.Code)
                {
                    case sf::Key::Escape :
                    app.Close();
                    break;
                    case sf::Key::G : // Game
                    std::cout << "Game starting" << std::endl;
                    myMode = GAME;
                    break;
                    case sf::Key::E : // Editeur
                    std::cout << "Editor starting" << std::endl;
                    myMode = EDIT;
                    break;
                    default:
                    break;
                }
                break;
                default:
                break;
            }
        }
        if(myMode==GAME)
            game->run();
        if(myMode==EDIT)
            editMap->run();

        myMode = DEF;

        app.Clear();
        app.Draw(menu); // Affichage menu
        app.Display();
    }
    // Libération mémoire
    delete game;
    delete editMap;

    return EXIT_SUCCESS;
}
