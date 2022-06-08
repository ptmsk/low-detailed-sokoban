#ifndef LEVEL_H_
#define LEVEL_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include "constant.h"

class Level : public sf::Drawable, public sf::Transformable
{
    private:
        int **structure;
        int level;
        int width;
        int height;
        int missing_target;
        sf::Texture texture;
        sf::VertexArray l_vertices;
        sf::Transform map_scale;
        sf::Vector2u player_position;
    
    public:
        Level(const Level&) = delete;
        Level& operator=(const Level&) = delete;
        Level();
        ~Level();
        int getLevel() const { return level; }
        void loadLevel(const int& level);
        bool isBig() { return (height > 8 || width > 13); }
        bool isFinalLevel() { return level == LEVEL_NUM; }
        float createScale();
        void update();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        const sf::Vector2u& getPlayerPosition() const { return player_position; }
        const sf::Vector2u getSize() const { return sf::Vector2u(SPRITESIZE * width, SPRITESIZE * height); }
        void try2Move(Direction dir);
        bool isFinished() { return missing_target == 0; }
};

#endif