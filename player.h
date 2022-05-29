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

        template<typename ... Args>
        void setPosition(Args&& ... args)
        {
            p_sprite.setPosition(std::forward<Args>(args) ...);
        }

        void update();
        bool isMoving;
        void setPosition(sf::Vector2u d);
        void setDirection(sf::Vector2f d);
        void setSprite(Direction dir);

};

#endif