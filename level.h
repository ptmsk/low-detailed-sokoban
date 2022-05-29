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
        sf::Vector2u player_position;
    
    public:
        Level(const Level&) = delete;
        Level& operator=(const Level&) = delete;
        Level();
        ~Level();
        void loadLevel(const int& level);
        void update();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        sf::Vector2u getPlayerPosition() { return player_position; }
        sf::Vector2u getSize() { return sf::Vector2u(SPRITESIZE * width, SPRITESIZE * height); }
        void try2Move(Direction dir);
        bool isFinished() { return missing_target == 0; }
};

#endif