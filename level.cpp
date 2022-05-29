#include "level.h"
#include "constant.h"
#include <iostream>
#include <fstream>
#include <sstream>

Level::Level() : structure(NULL), level(0), width(0), height(0)
{
    if (!texture.loadFromFile("assets/images/structure.png"))
        std::cout << "structure texture cannot load image.\n";
    
    l_vertices.setPrimitiveType(sf::Quads);
}

void Level::loadLevel(const int& level)
{
    this->level = level;
    std::ifstream file("assets/level/level" + std::to_string(level) + ".txt");
    std::string line;
    std::getline(file, line);
    std::stringstream ss(line);
    ss >> width;
    ss >> height;
    structure = new int*[height];
    for (int i = 0; i < height; i++)
    {
        structure[i] = new int[width];
        std::getline(file, line);
        std::stringstream ss(line);
        for (int j = 0; j < width; j++)
        {
            ss >> structure[i][j];
            if (structure[i][j] == PLAYER)
            {
                player_position.x = j;
                player_position.y = i;
            }
        }
    }


    file.close();
}

void Level::load()
{
    l_vertices.resize(width * height * 4);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // get the current tile number
            int tileNumber = structure[j][i];

            if (tileNumber == PLAYER)
                tileNumber = GROUND;

            // find its location in the tiletset texure
            int tu = tileNumber % (texture.getSize().x / SPRITESIZE);
            int tv = tileNumber / (texture.getSize().x / SPRITESIZE);

            // get a pointer to the current tile's squad.
            sf::Vertex *quad = &l_vertices[(i + j * width) * 4];

            // define 4 corners
            quad[0].position = sf::Vector2f(i * SPRITESIZE, j * SPRITESIZE);
            quad[1].position = sf::Vector2f((i + 1) * SPRITESIZE, j * SPRITESIZE);
            quad[2].position = sf::Vector2f((i + 1) * SPRITESIZE, (j + 1) * SPRITESIZE);
            quad[3].position = sf::Vector2f(i * SPRITESIZE, (j + 1) * SPRITESIZE);


            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * SPRITESIZE, tv * SPRITESIZE);
            quad[1].texCoords = sf::Vector2f((tu + 1) * SPRITESIZE, tv * SPRITESIZE);
            quad[2].texCoords = sf::Vector2f((tu + 1) * SPRITESIZE, (tv + 1) * SPRITESIZE);
            quad[3].texCoords = sf::Vector2f(tu * SPRITESIZE, (tv + 1) * SPRITESIZE);
        }
    }
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //* apply the transform
    states.transform *= getTransform();

    //* apply the tileset texture
    states.texture = &texture;

    //* draw the vertex array
    target.draw(l_vertices, states);
}