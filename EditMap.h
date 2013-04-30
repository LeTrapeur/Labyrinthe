#ifndef EDITMAP_H
#define EDITMAP_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Thread.hpp>
#include <sstream>
#include <fstream>
#include <vector>

#include "Tile.h"

class EditMap:
{
    public:
        EditMap(sf::RenderWindow& app, int nbTileX, int nbTileY,int tileW, int tileH);

        void run();
        void recordLvl();
        void loadLvl();
        void clearMap();
        void drawConstruction();

        void putTile(int x, int y);
        void delTile(int x, int y);
        void setTimeObj();

    private:
        sf::RenderWindow& m_app;
        int m_nbTileX;
        int m_nbTileY;
        int m_tileW;
        int m_tileH;

        bool m_isRunning;
        enum State{MAPSET,TIMESET};
        EditMap::State m_state;

        Tile til_tabMap[20][15];
        double m_timeObj;
        std::vector<char> m_tablvl;


        Tile til_actuel;

        Tile til_floor;
        Tile til_grass;
        Tile til_wall;
        Tile til_empty;
};



#endif // EDITMAP_H
