#ifndef GAME_H_
#define GAME_H_
#include <SFML/Graphics.hpp>
#include "player.cpp"
#include "level.cpp"

class Game 
{
    private:
        sf::RenderWindow window;
        Level level;
        Player player;

        void processEvents();
        void update();
        void render();

    public:
        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;
        Game();
        void run();
};

#endif