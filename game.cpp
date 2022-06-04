#include "game.h"
#include "constant.h"
#include <iostream>

Game::Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Low-detailed-sokoban"), status(Status::Normal), player(), level() 
{
    font.loadFromFile("assets/font/arial.ttf");

    title.setFont(font);
    title.setOutlineColor(sf::Color::Black);
    title.setStyle(sf::Text::Bold);
    title.setCharacterSize(32);

    Button exit = Button("Exit");
    Button play_again = Button("Play Again");
    Button next_level = Button("Next level");
    buttons.push_back(exit);
    buttons.push_back(play_again);
    buttons.push_back(next_level);

    sf::Vector2f exit_size = buttons[0].getSize();
    sf::Vector2f again_size = buttons[1].getSize();
    sf::Vector2f next_size = buttons[2].getSize();

    buttons[0].setPosition(15, WINDOW_HEIGHT - 70);
    buttons[1].setPosition(30 + exit_size.x, WINDOW_HEIGHT - 70);
    buttons[2].setPosition(45 + exit_size.x + again_size.x, WINDOW_HEIGHT - 70);
}

void Game::processEvents()
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::KeyPressed && !level.isFinished())
        {
            if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
            {
                level.try2Move(Direction::UP);
                player.setDirection(sf::Vector2f(0.0, -1.0));
                player.setSprite(Direction::UP);
            }
            else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
            {
                level.try2Move(Direction::DOWN);
                player.setDirection(sf::Vector2f(0.0, 1.0));
                player.setSprite(Direction::DOWN);
            }
            else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)
            {
                level.try2Move(Direction::LEFT);
                player.setDirection(sf::Vector2f(-1.0, 0.0));
                player.setSprite(Direction::LEFT);
            }
            else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
            {
                level.try2Move(Direction::RIGHT);
                player.setDirection(sf::Vector2f(1.0, 0.0));
                player.setSprite(Direction::RIGHT);
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased || event.type == sf::Event::MouseMoved)
        {
            for (int i = 0; i < BUTTON_NUM; i++)
            {
                if (buttons[i].processEvent(event))
                    status = Status(i);
            }
            
            if (level.isFinished() && buttons[BUTTON_NUM - 1].processEvent(event))
                status = Status::Next;
        }
    }
}

void Game::update()
{
    level.update();
    player.update(level);
}

void Game::render()
{
    window.clear(sf::Color(55, 138, 138, 1));

    for (int i = 0; i < BUTTON_NUM - 1; i++)
        window.draw(buttons[i]);

    if (level.isFinished())
    {
        title.setString("LEVEL " + std::to_string(level.getLevel()) + " - COMPLETED");
        title.setFillColor(sf::Color::Yellow); 
        
        window.draw(buttons[BUTTON_NUM - 1]);
    }

    window.draw(title);
    window.draw(level);
    window.draw(player);

    window.display();
}

void Game::run()
{   
    for (int l = 1; l <= LEVEL_NUM; l++)
    {
        status = Status::Normal;
        level.loadLevel(l);
        std::cout << "Ideal scale: " << level.createScale() << std::endl;
        title.setString("LEVEL " + std::to_string(l));
        title.setFillColor(sf::Color(255, 88, 74));

        float s = level.createScale();
        player.scale(s, s);

        sf::Vector2u board_size = level.getSize();
        float posx_board = WINDOW_WIDTH / 2.0f - board_size.x * s / 2.0f;
        float posy_board = WINDOW_HEIGHT / 2.0f - board_size.y * s / 2.0f;

        player.setOrigin(posx_board, posy_board);
        sf::Vector2u player_position = level.getPlayerPosition();
        player.setPosition(player_position);
        player.setSprite(Direction::DOWN);

        while (window.isOpen())
        {
            processEvents();
            update();
            render();

            if (status == Status::Closed)
                window.close();
            else if (status == Status::Again)
            {
                l--;
                std::cout << "Play again\n";
                break;
            }
            else if (status == Status::Next)
            {
                std::cout << "Next Level\n";
                break;
            }
        }

        player.scale(1 / s, 1 / s);
    }
}