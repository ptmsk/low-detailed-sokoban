#ifndef PLAYER_H_
#define PLAYER_H_

#include <SFML/Graphics.hpp>
#include <iostream>

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
        void update();
        bool isMoving;
        void setOrigin(float x, float y) { p_sprite.setOrigin(-x, -y); }
        void setPosition(sf::Vector2f d);
        sf::Vector2f getPosition() { return p_sprite.getPosition(); }
        void setDirection(sf::Vector2f d);
        sf::Vector2f getDirection() { return direction; }
        void setSprite(Direction dir);

};

#endif