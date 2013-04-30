#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <sstream>

#include "Tile.h"

class Level
{
    public:
        Level(sf::RenderWindow& app,int nbTileX, int nbTileY,int tileW, int tileH);

        void Draw();
        void loadLevel();
        void readLvl();

        Tile getTileLevel(int i,int j) const;
        int getTimeObj();

    private:
        sf::RenderWindow& m_app;
        int m_nbTileX;
        int m_nbTileY;
        int m_tileW;
        int m_tileH;

        Tile til_tabMap[20][15];
        double m_timeObj;
        std::vector<char> m_tablvl;

        Tile til_floor;
        Tile til_grass;
        Tile til_wall;
};

#endif // LEVEL_H
