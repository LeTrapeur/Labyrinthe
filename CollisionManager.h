#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Level.h"
#include "Tile.h"

class CollisionManager
{
    public:
        CollisionManager(Level* level);
        bool testMapCol(sf::IntRect& test);
        bool testFenCol(sf::IntRect& test) const;
        bool testWin(sf::IntRect& test);
        bool testEnemCol(sf::IntRect test1,sf::IntRect test2);
        void updateMap();
    private:
        Level* m_level;
        sf::IntRect m_mapBBX[20][15];
        Tile til_tabMap[20][15];
};

bool Collision(const sf::IntRect & a, const sf::IntRect & b);

#endif // COLLISIONMANAGER_H
