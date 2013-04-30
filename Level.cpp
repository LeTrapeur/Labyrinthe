#include "Level.h"

// Constructeur
Level::Level(sf::RenderWindow& app, int nbTileX, int nbTileY,int tileW, int tileH) : m_app(app),m_nbTileX(nbTileX), m_nbTileY(nbTileY), m_tileW(tileW), m_tileH(tileH),
til_floor(m_tileW,m_tileH,sf::Color(220,190,120),true,false), //Init tiles
til_grass(m_tileW,m_tileH,sf::Color(70,200,20),true,true),  //
til_wall(m_tileW,m_tileH,sf::Color(170,70,5),false,false)   // Fin init
{}
// Ecriture de la map dans la fenetre
void Level::Draw()
{
    for(int i(0); i<m_nbTileX; i++)
    {
        for(int j(0); j<m_nbTileY; j++)
            {
            m_app.Draw(til_tabMap[i][j].getShape());
            }
    }
}
//Chargement du Level
void Level::loadLevel()
{
    readLvl(); // Lecture du fichier niveau
    // Assignation positions Shapes
    for(int i(0); i<m_nbTileX; i++)
        {
            for(int j(0); j<m_nbTileY; j++)
                {
                    switch(m_tablvl[i*m_nbTileY+j])
                    {
                        case '0':
                        til_floor.SetPosition(i*m_tileW,j*m_tileH);
                        til_tabMap[i][j]=til_floor;
                        break;
                        case '1':
                        til_grass.SetPosition(i*m_tileW,j*m_tileH);
                        til_tabMap[i][j]=til_grass;
                        break;
                        case '2':
                        til_wall.SetPosition(i*m_tileW,j*m_tileH);
                        til_tabMap[i][j]=til_wall;
                        break;
                        default:
                        break;
                    }
                }
        }
    // Assignation temps Obj
    m_timeObj=0;
    std::string buff("");
    for(int i(m_nbTileX*m_nbTileY); i<(int)m_tablvl.size();i++) // On lit à partir de la fin des tiles
    {
        buff+=m_tablvl[i];
    }
    std::istringstream iss; // String -> Double
    iss.str(buff);
    iss>>m_timeObj;
}
// Lecture du fichier niveau
void Level::readLvl()
{
    m_tablvl.clear(); // Vide le précédent tableau texte niveau
    std::string path("rsc/lvl.txt");
    std::ifstream flux(path.c_str());
    // Lecture de la map
    if(flux)
        {
            while(!(flux.eof()))
                {
                    char a(0);
                    flux.get(a);
                    m_tablvl.push_back(a);
                }
        }
    else
        std::cerr << "Failed openning lvl.txt" << std::endl;
}
// Renvoie la Tile
Tile Level::getTileLevel(int i,int j) const
{
    return til_tabMap[i][j];
}
// Renvoie le temps necessaire pour le niveau
int Level::getTimeObj()
{
    return m_timeObj;
}
