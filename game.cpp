#include "game.h"
#include "constant.h"
#include <iostream>

Game::Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "test"), player(), level() {}

void Game::processEvents()
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
                window.close();
            else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
            {
                std::cout << "Up" << std::endl;
                player.isMoving = true;
                player.setDirection(sf::Vector2f(0.0, -1.0));
                player.setSprite(Direction::UP);
            }
            else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
            {
                std::cout << "Down" << std::endl;
                player.isMoving = true;
                player.setDirection(sf::Vector2f(0.0, 1.0));
                player.setSprite(Direction::DOWN);
            }
            else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)
            {
                std::cout << "Left" << std::endl;
                player.isMoving = true;
                player.setDirection(sf::Vector2f(-1.0, 0.0));
                player.setSprite(Direction::LEFT);
            }
            else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
            {
                std::cout << "Right" << std::endl;
                player.isMoving = true;
                player.setDirection(sf::Vector2f(1.0, 0.0));
                player.setSprite(Direction::RIGHT);
            }
        }
        else if (event.type = sf::Event::KeyReleased)
            player.isMoving = false;
    }
}

void Game::update()
{
    player.update();
}

void Game::render()
{
    window.clear();

    /*
    * draw here
    */
   window.draw(level);
   window.draw(player);

   window.display();
}

void Game::run()
{
    int l = 1;
    level.loadLevel(l);
    level.load();
    sf::Vector2u player_position = level.getPlayerPosition();
    player.setPosition(player_position);
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}