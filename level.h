#ifndef LEVEL_H_
#define LEVEL_H_

#include <SFML/Graphics.hpp>
#include <iostream>

class Level : public sf::Drawable, public sf::Transformable
{
    private:
        int **structure;
        int level;
        int width;
        int height;
        sf::Texture texture;
        sf::VertexArray l_vertices;
        sf::Vector2f player_position;
    
    public:
        Level(const Level&) = delete;
        Level& operator=(const Level&) = delete;
        Level();
        ~Level();
        void loadLevel(const int& level);
        void load();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        sf::Vector2f getPlayerPosition() { return player_position; }
        sf::Vector2f getSize() { return float(SPRITESIZE) * sf::Vector2f(width, height); }
};

#endif