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
    {
        sf::Vector2f p_pos = p_sprite.getPosition() + SPEED * direction;
        if (p_pos.x >= SPRITESIZE && p_pos.x <= 8 * 64 - 2 * SPRITESIZE && 
            p_pos.y >= SPRITESIZE && p_pos.y <= 8 * 64 - 2 * SPRITESIZE)
        {
            p_sprite.move(SPEED * direction);
        }
            // p_sprite.move(SPEED * direction);
    }
    std::cout << p_sprite.getPosition().x << ' ' << p_sprite.getPosition().y << std::endl;
}

void Player::setPosition(sf::Vector2f d)
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