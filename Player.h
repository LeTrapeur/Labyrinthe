#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "CollisionManager.h"

// TODO Créer un classe affichePlayer et CoolManager et Serialisation player


class Player
{
    public:
        // Création
        Player(CollisionManager colManag);
        void init();
        // Affichage
        sf::Sprite getSprite() const;
        sf::IntRect getBoundingBox() const;
        // Actions
        enum Direction{TOP,BOTTOM,LEFT,RIGHT};
        void Move(Direction dir);
        void evolue(sf::RenderWindow& app);
        // Gestion Collisions
        int testDeplctT(int y);
        int testDeplctB(int y);
        int testDeplctL(int x);
        int testDeplctR(int x);
        bool testObjectif();

    private:
        int m_x;
        int m_y;

        int m_speed;
        float m_frame;

        sf::Sprite m_sprite;
        sf::Image m_img;

        CollisionManager m_colManag;

};



#endif // PLAYER_H
