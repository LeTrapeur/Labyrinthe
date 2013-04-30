#ifndef GAME_H
#define GAME_H

#include <sstream>
#include <iomanip>

#include "Level.h"
#include "CollisionManager.h"
#include "Player.h"
#include "Enemy.h"



// TODO Gestion niveaux
class Game
{
    public:
         Game();
         Game(sf::RenderWindow& app);
        ~Game();

        void run();
        void win();
        void lose();

    private:
        sf::RenderWindow& m_app;

        bool m_isRunning;
        sf::Clock m_timer;
        sf::Font m_font;
        sf::String m_chrono;

        Level *m_level;
        CollisionManager *m_colManag;
        Player *m_player;
        Enemy *m_enemy;
        Enemy *m_enemy2;                                //

};

#endif // GAME_H
