#include "game.h"
#include <iostream>

Game::Game() : window(sf::VideoMode(800, 600), "test"), player(150)
{
    player.setFillColor(sf::Color::Blue);
    player.setPosition(10, 20);
}

void Game::processEvents()
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            window.close();
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
            {
                std::cout << "Up" << std::endl;
            }
            else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
            {
                std::cout << "Down" << std::endl;
            }
            else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)
            {
                std::cout << "Left" << std::endl;
            }
            else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
            {
                std::cout << "Right" << std::endl;
            }
        }
    }
}

void Game::update()
{

}

void Game::render()
{
    window.clear();

    /*
    * draw here
    */
   
   window.draw(player);

   window.display();
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}