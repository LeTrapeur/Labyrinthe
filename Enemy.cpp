#include "Enemy.h"
#include "Constantes.h"

// Constructeur
Enemy::Enemy(CollisionManager colManag, int x, int y): m_colManag(colManag)     //
{
    // Init Enemy
    if(m_img.LoadFromFile("rsc/enemy.bmp"))
        m_sprite.SetImage(m_img);
    else
        std::cerr << "Failed openning enemy.bmp" << std::endl;

        m_spawnX=x;
        m_spawnY=y;

        init();
}
void Enemy::init()
{
    // TODO test d'initialisation
    m_x=m_spawnX;                          //
    m_y=m_spawnY;                          //
    m_sprite.SetPosition(m_x,m_y);
    m_speed=190;
}
// Retourne sprite Enemy
sf::Sprite Enemy::getSprite() const
{
    return m_sprite;
}
// Retourne rectangle Enemy pour test collision
sf::IntRect Enemy::getBoundingBox() const
{
    sf::IntRect m_boundingBox;
    m_boundingBox.Left = (int)m_sprite.GetPosition().x;
    m_boundingBox.Right = m_boundingBox.Left + m_sprite.GetSize().x;
    m_boundingBox.Top = (int)m_sprite.GetPosition().y;
    m_boundingBox.Bottom = m_boundingBox.Top + m_sprite.GetSize().y;
    return m_boundingBox;
}
// deplacement joueur
void Enemy::Move(Direction dir)
{
    switch(dir)
    {
        case Enemy::TOP :
        m_y = testDeplctT(-m_speed*m_frame); // On lui envoie la position à tester pour le dplct
        m_sprite.SetPosition(m_x,m_y);
        break;
        case Enemy::BOTTOM :
        m_y = testDeplctB(m_speed*m_frame); //
        m_sprite.SetPosition(m_x,m_y);
        break;
        case Enemy::LEFT:
        m_x = testDeplctL(-m_speed*m_frame); //
        m_sprite.SetPosition(m_x,m_y);
        break;
        case Enemy::RIGHT:
        m_x = testDeplctR(m_speed*m_frame); // Idem
        m_sprite.SetPosition(m_x,m_y);
        break;
        default :
        break;
    }
}
// Actions joueur
void Enemy::evolue(sf::RenderWindow& app, int playerX, int playerY)
{
    m_frame = app.GetFrameTime();
    // Déplacement à la souris
    if(m_sprite.GetPosition().y > playerY)
    Move(Enemy::TOP);
    else if(m_sprite.GetPosition().y < playerY)
    Move(Enemy::BOTTOM);
    if(m_sprite.GetPosition().x > playerX)
    Move(Enemy::LEFT);
    else if(m_sprite.GetPosition().x < playerX)
    Move(Enemy::RIGHT);
}


int Enemy::testDeplctT(int y)
{
    sf::IntRect test;
    test = getBoundingBox();
    test.Top+=y;
    if(m_colManag.testMapCol(test) || m_colManag.testFenCol(test))
        {
            for(int i(0); i<m_speed;i++)
                {
                    if(m_colManag.testMapCol(test)==false&&m_colManag.testFenCol(test)==false)
                    break;
                    else
                    test.Top+=1;
                }
        }
    return test.Top;
}
int Enemy::testDeplctB(int y)
{
    sf::IntRect test;
    test = getBoundingBox();
    test.Bottom+=y;
    if(m_colManag.testMapCol(test)|| m_colManag.testFenCol(test))
        {
            for(int i(0); i<m_speed;i++)
                {
                    if(m_colManag.testMapCol(test)==false&&m_colManag.testFenCol(test)==false)
                    break;
                    else
                    test.Bottom-=1;
                }

        }
    return test.Bottom-(m_sprite.GetSize().y);
}
int Enemy::testDeplctL(int x)
{
    sf::IntRect test;
    test = getBoundingBox();
    test.Left+=x;
    if(m_colManag.testMapCol(test)|| m_colManag.testFenCol(test))
        {
            for(int i(0); i<m_speed;i++)
                {
                    if(m_colManag.testMapCol(test)==false&&m_colManag.testFenCol(test)==false)
                    break;
                    else
                    test.Left+=1;
                }

        }
    return test.Left;
}
int Enemy::testDeplctR(int x)
{
    sf::IntRect test;
    test = getBoundingBox();
    test.Right+=x;
    if(m_colManag.testMapCol(test)|| m_colManag.testFenCol(test))
        {
            for(int i(0); i<m_speed;i++)
                {
                    if(m_colManag.testMapCol(test)==false&&m_colManag.testFenCol(test)==false)
                    break;
                    else
                    test.Right-=1;
                }

        }
    return test.Right-(m_sprite.GetSize().x);
}
