#include "Player.h"
#include "Constantes.h"



// Constructeur
Player::Player(CollisionManager colManag): m_colManag(colManag)
{
    // Init player
    if(m_img.LoadFromFile("rsc/player.bmp"))
        m_sprite.SetImage(m_img);
    else
        std::cerr << "Failed openning player.bmp" << std::endl;

    init();
}
void Player::init()
{
    // TODO test d'initialisation
    m_x=10;
    m_y=20;
    m_sprite.SetPosition(m_x,m_y);
    m_speed=200;
}
// Retourne sprite player
sf::Sprite Player::getSprite() const
{
    return m_sprite;
}
// Retourne rectangle player pour test collision
sf::IntRect Player::getBoundingBox() const
{
    sf::IntRect m_boundingBox;
    m_boundingBox.Left = (int)m_sprite.GetPosition().x;
    m_boundingBox.Right = m_boundingBox.Left + m_sprite.GetSize().x;
    m_boundingBox.Top = (int)m_sprite.GetPosition().y;
    m_boundingBox.Bottom = m_boundingBox.Top + m_sprite.GetSize().y;
    return m_boundingBox;
}
// deplacement joueur
void Player::Move(Direction dir)
{
    switch(dir)
    {
        case Player::TOP :
        m_y = testDeplctT(-m_speed*m_frame); // On lui envoie la position à tester pour le dplct
        m_sprite.SetPosition(m_x,m_y);
        break;
        case Player::BOTTOM :
        m_y = testDeplctB(m_speed*m_frame); //
        m_sprite.SetPosition(m_x,m_y);
        break;
        case Player::LEFT:
        m_x = testDeplctL(-m_speed*m_frame); //
        m_sprite.SetPosition(m_x,m_y);
        break;
        case Player::RIGHT:
        m_x = testDeplctR(m_speed*m_frame); // Idem
        m_sprite.SetPosition(m_x,m_y);
        break;
        default :
        break;
    }
}
// Actions joueur
void Player::evolue(sf::RenderWindow& app)
{
    const sf::Input& input = app.GetInput();
    m_frame = app.GetFrameTime();
    // Déplacement à la souris
    if(m_sprite.GetPosition().y > input.GetMouseY()-PLAYER_SIZE/2)
    Move(Player::TOP);
    else if(m_sprite.GetPosition().y < input.GetMouseY()-PLAYER_SIZE/2)
    Move(Player::BOTTOM);
    if(m_sprite.GetPosition().x > input.GetMouseX()-PLAYER_SIZE/2)
    Move(Player::LEFT);
    else if(m_sprite.GetPosition().x < input.GetMouseX()-PLAYER_SIZE/2)
    Move(Player::RIGHT);
}


int Player::testDeplctT(int y)
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
int Player::testDeplctB(int y)
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
int Player::testDeplctL(int x)
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
int Player::testDeplctR(int x)
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

bool Player::testObjectif()
{
    sf::IntRect test;
    test = getBoundingBox();
    if(m_colManag.testWin(test))
        return true;
    else
        return false;
}


