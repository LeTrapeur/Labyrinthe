#include "EditMap.h"
#include "Constantes.h"

//Constructeur
EditMap::EditMap(sf::RenderWindow& app, int nbTileX, int nbTileY,int tileW, int tileH) :
m_app(app), m_nbTileX(nbTileX), m_nbTileY(nbTileY), m_tileW(tileW), m_tileH(tileH),
m_isRunning(true),
til_floor(m_tileW,m_tileH,sf::Color(220,190,120),true,false), //Init tiles
til_grass(m_tileW,m_tileH,sf::Color(70,200,20),true,true),  //
til_wall(m_tileW,m_tileH,sf::Color(170,70,5),false,false),  //
til_empty(m_tileW,m_tileH,sf::Color(0,0,0),true,false)       //
{
    til_actuel=til_floor; // Shape par defaut

}
//Boucle d'edition
void EditMap::run()
{
    m_state=EditMap::MAPSET; // On commence par défaut en mode édition de la map
    m_isRunning=true; //init
    while (m_isRunning)
    {
        sf::Event event;
        while (m_app.GetEvent(event))
        {
            switch(event.Type) // Test de l'event
            {
                case sf::Event::Closed :
                m_app.Close();
                break;
                case sf::Event::KeyPressed : // Test touche
                switch(event.Key.Code)
                {
                    case sf::Key::Escape :
                    m_isRunning=false;
                    std::cout << "Editor exiting" << std::endl;
                    break;
                    case sf::Key::R :
                    recordLvl();
                    std::cout << "Level recorded" << std::endl;
                    break;
                    case sf::Key::L :
                    loadLvl();
                    std::cout << "Level loaded" << std::endl;
                    break;
                    case sf::Key::D :
                    clearMap();
                    std::cout << "Clear map done" << std::endl;
                    break;
                    case sf::Key::T :
                    m_state=EditMap::TIMESET; // On passe en mode édition du temps
                    break;
                    case sf::Key::F :
                    til_actuel=til_floor;
                    til_actuel.SetPosition(event.MouseButton.X-(m_tileW/2),event.MouseButton.Y-(m_tileH/2)); // On actualise pos pour éviter (0,0)
                    break;
                    case sf::Key::G :
                    til_actuel=til_grass;
                    til_actuel.SetPosition(event.MouseMove.X-(m_tileW/2),event.MouseMove.Y-(m_tileH/2));
                    break;
                    case sf::Key::W :
                    til_actuel=til_wall;
                    til_actuel.SetPosition(event.MouseMove.X-(m_tileW/2),event.MouseMove.Y-(m_tileH/2));
                    break;
                    default:
                    break;
                }
                break;
                case sf::Event::MouseMoved : // mvt souris
                til_actuel.SetPosition(event.MouseMove.X-(m_tileW/2),event.MouseMove.Y-(m_tileH/2)); // Mvt tile selectionné
                break;
                case sf::Event::MouseButtonPressed :
                switch(event.MouseButton.Button) // Test bouton souris
                {
                    case sf::Mouse::Left :
                    putTile(event.MouseButton.X,event.MouseButton.Y);
                    break;
                    case sf::Mouse::Right :
                    delTile(event.MouseButton.X,event.MouseButton.Y);
                    break;
                    default:
                    break;
                }
                break;
                default:
                break;
            }
        }
        m_app.Clear();

        if(m_state==EditMap::TIMESET)
            setTimeObj();

        drawConstruction();

        m_app.Display();
    }
}
// Ecriture d'un fichier .txt pour stocker niveau
void EditMap::recordLvl()
{
    std::ofstream flux("rsc/lvl.txt");
    if (flux)
    {
        for(int i(0);i<m_nbTileX;i++) // Carte
        {
            for(int j(0);j<m_nbTileY;j++)
            {
                if(til_tabMap[i][j]==til_floor)
                    flux << '0';
                else if(til_tabMap[i][j]==til_grass)
                    flux << '1';
                else if(til_tabMap[i][j]==til_wall)
                    flux << '2';
                else
                    flux << '0';
            }
        }
        flux << m_timeObj; // Time
    }
    else
    std::cerr << "Failed openning lvl.txt" << std::endl;
}
// Charge niveau
void EditMap::loadLvl()
{
    m_tablvl.clear(); // Vide le précédent tableau texte niveau
    std::string path("rsc/lvl.txt");
    std::ifstream flux(path.c_str());
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
}
// Efface la carte
void EditMap::clearMap() // La fonction est similaire à un draw
{
    for(int i(0); i<m_nbTileX; i++)
    {
        for(int j(0); j<m_nbTileY; j++)
        {
            til_empty.SetPosition(i*m_tileW,j*m_tileH); // On remplit toutes les positions de vide
            til_tabMap[i][j]=til_empty; // et on en remplit le tableau de til_vide
        }
    }
}
// Dessine la construction de la mat
void EditMap::drawConstruction()
{
    for(int i(0); i<m_nbTileX; i++)
        {
            for(int j(0); j<m_nbTileY; j++)
            {
                m_app.Draw(til_tabMap[i][j].getShape()); // Affiche la map en construction
            }
        }
        m_app.Draw(til_actuel.getShape()); // Affiche le shape selectionné
}
// Assigne une tile
void EditMap::putTile(int x, int y)
{
    til_actuel.SetPosition((x/m_tileW)*m_tileW,(y/m_tileH)*m_tileH); // Position pour tableau de tiles
    til_tabMap[x/m_tileW][y/m_tileH]=til_actuel; // Charge le tableau avec la tile repositionnée
}
// Même fonctionnement que putTile mais avec tile vide
void EditMap::delTile(int x, int y)
{
    til_empty.SetPosition((x/m_tileW)*m_tileW,(y/m_tileH)*m_tileH);
    til_tabMap[x/m_tileW][y/m_tileH]=til_empty;
}
// Affichage du "menu" gérant la selection du temps
void EditMap::setTimeObj()
{
    bool run(true);
    sf::Font font;
    font.LoadFromFile("rsc/digital7.ttf",30);
    sf::String str("Time : ",font,50);
    str.SetColor(sf::Color::Red);
    str.SetPosition(((NB_TILE_X*TILE_WIDTH)/2)-(str.GetRect().GetWidth()/2),(NB_TILE_Y*TILE_HEIGHT)/2-(50/2));

    sf::String Text("",font,50);
    Text.SetColor(sf::Color::Red);
    Text.SetPosition((((NB_TILE_X*TILE_WIDTH)/2)-(str.GetRect().GetWidth()/2))+str.GetRect().GetWidth(),(NB_TILE_Y*TILE_HEIGHT)/2-(50/2));
    std::string buff("");

    while(run)
    {
        sf::Event event;
        while(m_app.GetEvent(event))
        {
            if(event.Type == sf::Event::TextEntered)
            {
                buff += event.Text.Unicode;
                Text.SetText(buff);
            }
            else if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Return)
            {
                std::istringstream iss; // String -> Double
                iss.str(buff);
                iss>>m_timeObj;
                run=false;
                m_state=EditMap::MAPSET; // On revient à la gestion de la map
            }
        }
        m_app.Clear();
        drawConstruction();
        m_app.Draw(Text);
        m_app.Draw(str);
        m_app.Display();
    }
}
