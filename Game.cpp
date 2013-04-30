#include "Game.h"
#include "Constantes.h"

// Constructeur
Game::Game(sf::RenderWindow& app): m_app(app), m_isRunning(true)
{
    // Init Level
    m_level = new Level(m_app,NB_TILE_X,NB_TILE_Y,TILE_WIDTH,TILE_HEIGHT);
    //Init CollisionManager
    m_colManag = new CollisionManager(m_level);
    // Init Player
    m_player = new Player(*m_colManag); // Déférencement de pointeur
    // Init Enemy
    m_enemy = new Enemy(*m_colManag, 760, 0); // Déférencement de pointeur
    m_enemy2 = new Enemy(*m_colManag, 10, 540 ); // Déférencement de pointeur                        //
    //Init Font
    const int FONT_SIZE(30);
    if(!m_font.LoadFromFile("rsc/digital7.ttf",FONT_SIZE))
        std::cout << "Failed openning Font" << std::endl;
    //Init chrono
    m_chrono.SetFont(m_font);
    m_chrono.SetColor(sf::Color::Red);
    m_chrono.SetSize(FONT_SIZE);
    m_chrono.SetPosition(750,0);
}
// Destructeur
Game::~Game()
{
    delete m_level;
    delete m_colManag;
    delete m_player;
    delete m_enemy;
    delete m_enemy2;                                                                         //
}
//Boucle de jeu
void Game::run()
{
    m_level->loadLevel(); // On charge le niveau
    m_timer.Reset();  // RAZ compteur
    m_player->init(); // On remet le player au départ
    m_enemy->init(); // On remet l'enemy au départ
    m_enemy2->init();                                                                       //
    m_isRunning=true; //init la boucle
    while (m_isRunning)
    {
        sf::Event event;
        while (m_app.GetEvent(event))
        {
            switch(event.Type)
            {
                case sf::Event::Closed :
                m_app.Close();
                break;
                case sf::Event::KeyPressed :
                switch(event.Key.Code)
                {
                    case sf::Key::Escape :
                    m_isRunning=false;
                    //std::cout << "Game exiting" << std::endl;
                    break;
                    case sf::Key::L :
                    m_level->loadLevel(); // Chargement d'un niveau
                    m_timer.Reset(); // RAZ compteur
                    m_player->init(); // On remet le player au départ
                    std::cout << "Level loaded" << std::endl;
                    break;
                    default:
                    break;
                }
                break;
                default:
                break;
            }
        }
        // Clear fenetre
        m_app.Clear();
        //Affichage de la map (On passe par une fonction pour éviter la surcharge) A AFFICHER AVANT
        m_level->Draw();
        // Gère les actions des personnages
        m_player->evolue(m_app);
        if(m_timer.GetElapsedTime() > 1)
        {
            m_enemy->evolue(m_app, m_player->getSprite().GetPosition().x, m_player->getSprite().GetPosition().y);
            m_enemy2->evolue(m_app, m_player->getSprite().GetPosition().x, m_player->getSprite().GetPosition().y);              //
        } // Temps pour démarrer

        // Test obj
        if(m_player->testObjectif())
            win();
         // Chronometre du jeu
        else if(m_timer.GetElapsedTime() >= m_level->getTimeObj() || m_colManag->testEnemCol(m_player->getBoundingBox(),m_enemy->getBoundingBox()) || m_colManag->testEnemCol(m_player->getBoundingBox(),m_enemy2->getBoundingBox())) // Si temps écoulé et joueur touché       //
            lose();
        //Affichage des personnages
        m_app.Draw(m_player->getSprite());
        m_app.Draw(m_enemy->getSprite());
        m_app.Draw(m_enemy2->getSprite());              //
        //Affichage chrono
        std::ostringstream oss; // Double -> String
        oss<< std::setprecision(3) << (m_level->getTimeObj()-m_timer.GetElapsedTime()); // Affichage Décompteur avec modification précision double
        m_chrono.SetText(oss.str());
        m_app.Draw(m_chrono);
        // Update fenetre
        m_app.Display();
    }
    std::cout << "Game exiting" << std::endl;
}
// TODO Win et lose similaire implémentation GUI, MENU ?
void Game::win()
{
    const int FONT_SIZE(50);
    sf::String str("You Win !",m_font,FONT_SIZE);
    str.SetColor(sf::Color::Red);
    str.SetPosition(((NB_TILE_X*TILE_WIDTH)/2)-(str.GetRect().GetWidth()/2),(NB_TILE_Y*TILE_HEIGHT)/2-(FONT_SIZE/2));
    m_app.Draw(str);
    m_app.Display();
    sf::Sleep(2.0f);
    m_isRunning=false;
}

void Game::lose()
{
    const int FONT_SIZE(50);
    sf::String str("You Lose !",m_font,FONT_SIZE);
    str.SetColor(sf::Color::Red);
    str.SetPosition(((NB_TILE_X*TILE_WIDTH)/2)-(str.GetRect().GetWidth()/2),(NB_TILE_Y*TILE_HEIGHT)/2-(FONT_SIZE/2));
    m_app.Draw(str);
    m_app.Display();
    sf::Sleep(2.0f);
    m_isRunning=false;
}
