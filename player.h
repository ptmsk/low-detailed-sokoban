#ifndef PLAYER_H_
#define PLAYER_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include "level.h"

class Player : public sf::Drawable
{
    private:
        sf::Texture p_texture;
        sf::Sprite p_sprite;
        sf::Vector2f direction;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    public:
        Player(const Player&) = delete;
        Player& operator=(const Player&) = delete;
        Player();
        void update(Level &level);
        void scale(float x, float y) { p_sprite.scale(x, y); }
        void setOrigin(float x, float y) { p_sprite.setOrigin(-x, -y); }
        void setPosition(sf::Vector2u d);
        const sf::Vector2f& getPosition() const { return p_sprite.getPosition(); }
        void setDirection(sf::Vector2f d);
        const sf::Vector2f& getDirection() const { return direction; }
        void setSprite(Direction dir);
};

#endif