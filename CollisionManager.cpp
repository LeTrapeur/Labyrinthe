#include "CollisionManager.h"
// TODO Constantes magiques
bool Collision(const sf::IntRect & a, const sf::IntRect & b)
{
    if (a.Bottom <= b.Top)
        return false;
    if (a.Top >= b.Bottom)
        return false;
    if (a.Right <= b.Left)
        return false;
    if (a.Left >= b.Right)
        return false;

    return true;
}

CollisionManager::CollisionManager(Level* level): m_level(level)
{updateMap();}

bool CollisionManager::testMapCol(sf::IntRect& test)
{
    updateMap(); // Fais chier enleve le const mais permet d'actualiser la map pour séparer les classes
    for(int i(0); i<20; i++)
    {
        for(int j(0); j<15; j++)
            {
                if(!(til_tabMap[i][j].getEmpty()) && Collision(m_mapBBX[i][j],test))
                    return true;
            }
    }
    return false;
}

bool CollisionManager::testFenCol(sf::IntRect& test) const
{
    if(test.Top < 0 || test.Bottom > 600 || test.Left < 0 || test.Right > 800)
    return true;
    else
    return false;
}

void CollisionManager::updateMap()
{
        // On charge les tiles pour tester ensuite les vide et on charge les boundingbox de la map
    for(int i(0); i<20; i++)
    {
        for(int j(0); j<15; j++)
            {
                til_tabMap[i][j]=m_level->getTileLevel(i,j);
                m_mapBBX[i][j]=til_tabMap[i][j].getBoundingBox();
            }
    }
}

bool CollisionManager::testWin(sf::IntRect& test)
{
    updateMap(); // Fais chier enleve le const mais permet d'actualiser la map pour séparer les classes
    for(int i(0); i<20; i++)
    {
        for(int j(0); j<15; j++)
            {
                if(til_tabMap[i][j].getWin() && Collision(m_mapBBX[i][j],test))
                    return true;
            }
    }
    return false;
}

bool CollisionManager::testEnemCol(sf::IntRect test1,sf::IntRect test2)
{
    if(Collision(test1,test2))
        return true;

    return false;
}




