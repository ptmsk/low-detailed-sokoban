#ifndef GAME_H_
#define GAME_H_
#include <SFML/Graphics.hpp>
#include "player.cpp"

class Game 
{
    private:
        sf::RenderWindow window;
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