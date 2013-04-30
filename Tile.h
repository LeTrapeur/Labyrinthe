#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

class Tile
{
    public:
        Tile();
        Tile(int tileW, int tileH, sf::Color tileColor, bool empty, bool win);

        void SetPosition(int x,int y);

        sf::Shape getShape() const;
        sf::IntRect getBoundingBox() const;
        bool getEmpty() const;
        bool getWin() const;

        bool isEqual(Tile const& b)const;

    private:
        int m_tileW;
        int m_tileH;

        sf::Color m_tileColor;

        sf::Shape sh_tile;
        sf::IntRect m_boundingBox;

        bool m_empty;
        bool m_win;
};

bool operator==(Tile const& a, Tile const& b);
#endif // TILE_H
