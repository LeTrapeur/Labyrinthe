#include "Tile.h"

// Constructeurs
Tile::Tile(){}
Tile::Tile(int tileW, int tileH, sf::Color tileColor, bool empty, bool win):
m_tileW(tileW), m_tileH(tileH), m_tileColor(tileColor), m_empty(empty), m_win(win)
{
    sh_tile.AddPoint(0,0);
    sh_tile.AddPoint(m_tileW,0);
    sh_tile.AddPoint(m_tileW,m_tileH);
    sh_tile.AddPoint(0,m_tileH);
    sh_tile.SetColor(m_tileColor);
}
 // Assigne la position à un shape permettant de l'afficher avec sf::Draw()
void Tile::SetPosition(int x,int y)
{
    sh_tile.SetPosition(x,y);
}
// Retourne shape de la tile
sf::Shape Tile::getShape() const
{
    return sh_tile;
}
// Retourne le rectangle entourant la tile pour test collision
sf::IntRect Tile::getBoundingBox() const
{
    sf::IntRect boundingBox;
    boundingBox.Left = (int)sh_tile.GetPosition().x;
    boundingBox.Right = boundingBox.Left + m_tileW;
    boundingBox.Top = (int)sh_tile.GetPosition().y;
    boundingBox.Bottom = boundingBox.Top + m_tileH;
    return boundingBox;
}
// Cassable ou non
bool Tile::getEmpty() const
{
    return m_empty;
}
// Cassable ou non
bool Tile::getWin() const
{
    return m_win;
}
// Surcharge op=
bool Tile::isEqual(Tile const& b) const
{
    if(m_tileW == b.m_tileW && m_tileH == b.m_tileH && m_tileColor == b.m_tileColor)
    return true;
    else
    return false;
}
// Idem
bool operator==(Tile const& a, Tile const& b)
{
    return a.isEqual(b);
}
