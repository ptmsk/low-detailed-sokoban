#include "level.h"
#include <fstream>
#include <sstream>

Level::Level() : structure(NULL), level(0), width(0), height(0)
{
    if (!texture.loadFromFile("assets/images/structure.png"))
        std::cout << "structure texture cannot load image.\n";
    
    l_vertices.setPrimitiveType(sf::Quads);
}

Level::~Level()
{
    for (int i = 0; i < width; i++)
        delete [] structure[i];
    delete [] structure;
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
                structure[i][j] = GROUND;
                player_position.x = j;
                player_position.y = i;
            }
        }
    }


    file.close();
}

void Level::update()
{
    float posx_board = WINDOW_WIDTH / 2 - width * SPRITESIZE / 2.0f;
    float posy_board = WINDOW_HEIGHT / 2 - height * SPRITESIZE / 2.0f;
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
            quad[0].position = sf::Vector2f(i * SPRITESIZE + posx_board, j * SPRITESIZE + posy_board);
            quad[1].position = sf::Vector2f((i + 1) * SPRITESIZE + posx_board, j * SPRITESIZE + posy_board);
            quad[2].position = sf::Vector2f((i + 1) * SPRITESIZE + posx_board, (j + 1) * SPRITESIZE + posy_board);
            quad[3].position = sf::Vector2f(i * SPRITESIZE + posx_board, (j + 1) * SPRITESIZE + posy_board);


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

void Level::try2Move(Direction dir)
{
    int x = player_position.x;
    int y = player_position.y;
    if (dir == Direction::LEFT)
    {
        if (x > 0 && (structure[y][x - 1] == GROUND || structure[y][x - 1] == TARGET))
            // move to left
            player_position -= sf::Vector2u(1, 0);
        else if (x > 1 && (structure[y][x - 1] == BOX || structure[y][x - 1] == TARGET_FILLED) &&
                (structure[y][x - 2] == GROUND || structure[y][x - 2] == TARGET))
        {
            // move and push the box to left
            if (structure[y][x - 1] == TARGET_FILLED)
                structure[y][x - 1] = TARGET;
            else
                structure[y][x - 1] = GROUND;

            if (structure[y][x - 2] == GROUND)
                structure[y][x - 2] = BOX;
            else
                structure[y][x - 2] = TARGET_FILLED;

            player_position -= sf::Vector2u(1, 0);
        }
    }
    else if (dir == Direction::RIGHT)
    {
        if (x + 1 < width && (structure[y][x + 1] == GROUND || structure[y][x + 1] == TARGET))
            // move to right
            player_position += sf::Vector2u(1, 0);
        else if (x + 2 < width && (structure[y][x + 1] == BOX || structure[y][x + 1] == TARGET_FILLED) &&
                (structure[y][x + 2] == GROUND || structure[y][x + 2] == TARGET))
        {
            // move and push the box to right
            if (structure[y][x + 1] == TARGET_FILLED)
                structure[y][x + 1] = TARGET;
            else
                structure[y][x + 1] = GROUND;

            if (structure[y][x + 2] == GROUND)
                structure[y][x + 2] = BOX;
            else
                structure[y][x + 2] = TARGET_FILLED;

            player_position += sf::Vector2u(1, 0);
        }
    }
    else if (dir == Direction::UP)
    {
        if (y > 0 && (structure[y - 1][x] == GROUND || structure[y - 1][x] == TARGET))
            // move up
            player_position -= sf::Vector2u(0, 1);
        else if (y > 1 && (structure[y - 1][x] == BOX || structure[y - 1][x] == TARGET_FILLED) &&
                (structure[y - 2][x] == GROUND || structure[y - 2][x] == TARGET))
        {
            // move and push the box up
            if (structure[y - 1][x] == TARGET_FILLED)
                structure[y - 1][x] = TARGET;
            else
                structure[y - 1][x] = GROUND;

            if (structure[y - 2][x] == GROUND)
                structure[y - 2][x] = BOX;
            else
                structure[y - 2][x] = TARGET_FILLED;

            player_position -= sf::Vector2u(0, 1);
        }
    }
    else if (dir == Direction::DOWN)
    {
        if (y + 1 < height && (structure[y + 1][x] == GROUND || structure[y + 1][x] == TARGET))
            // move down
            player_position += sf::Vector2u(0, 1);
        else if (y + 2 < height && (structure[y + 1][x] == BOX || structure[y + 1][x] == TARGET_FILLED) &&
                (structure[y + 2][x] == GROUND || structure[y + 2][x] == TARGET))
        {
            // move and push the box down
            if (structure[y + 1][x] == TARGET_FILLED)
                structure[y + 1][x] = TARGET;
            else
                structure[y + 1][x] = GROUND;

            if (structure[y + 2][x] == GROUND)
                structure[y + 2][x] = BOX;
            else
                structure[y + 2][x] = TARGET_FILLED;

            player_position += sf::Vector2u(0, 1);
        }
    }
}