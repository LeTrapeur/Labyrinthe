#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "CollisionManager.h"

class Enemy
{
    public:
        // Création
        Enemy(CollisionManager colManag, int x, int y);         //
        void init();
        // Affichage
        sf::Sprite getSprite() const;
        sf::IntRect getBoundingBox() const;
        // Actions
        enum Direction{TOP,BOTTOM,LEFT,RIGHT};
        void Move(Direction dir);
        void evolue(sf::RenderWindow& app, int playerX, int playerY);
        // Gestion Collisions
        int testDeplctT(int y);
        int testDeplctB(int y);
        int testDeplctL(int x);
        int testDeplctR(int x);

    private:
        int m_x;
        int m_y;
        int m_spawnX;
        int m_spawnY;

        int m_speed;
        float m_frame;

        sf::Sprite m_sprite;
        sf::Image m_img;

        CollisionManager m_colManag;
};

#endif // ENEMY_H
