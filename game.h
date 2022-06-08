#ifndef GAME_H_
#define GAME_H_
#include <SFML/Graphics.hpp>
#include "player.cpp"
#include "level.cpp"
#include "button.cpp"
#include <vector>

#define BUTTON_NUM 3

class Game 
{
    private:
        enum Status { Normal = -1, Closed = 0, Again = 1, Next = 2 };
        Status status;
        sf::RenderWindow window;
        sf::Font font;
        sf::Text title;
        Level level;
        Player player;
        std::vector<Button> buttons; 

        void processEvents();
        void update();
        void render();

    public:
        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;
        Game();
        void run(const int& lastlevel = 1);
};

#endif