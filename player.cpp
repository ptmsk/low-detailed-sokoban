#include "constant.h"
#include "player.h"

Player::Player() : direction(sf::Vector2f(0.0, 0.0))
{
    if (!p_texture.loadFromFile("assets/images/player.png"))
        std::cout << "player texture cannot load image.\n";
    
    p_sprite.setTexture(p_texture);
    p_sprite.setTextureRect(sf::IntRect(64, 0, SPRITESIZE, SPRITESIZE));
}

void Player::update()
{
    if (isMoving)
        p_sprite.move(2.0f * direction);
}

void Player::setPosition(sf::Vector2u d)
{
    p_sprite.setPosition(d.x * SPRITESIZE, d.y * SPRITESIZE);
}

void Player::setDirection(sf::Vector2f d)
{
    direction = d;
}

void Player::setSprite(Direction dir)
{
    p_sprite.setTextureRect(sf::IntRect(64 * dir, 0, SPRITESIZE, SPRITESIZE));
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(p_sprite, states);
}