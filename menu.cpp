#include <iostream>
#include "menu.h"
#include "constant.h"

Menu::Menu(): selectedItemIndex(-1)
{
    font.loadFromFile("assets/font/Guava Candy.ttf");
    title.setFont(font);
    title.setCharacterSize(200);
    title.setFillColor(sf::Color(255, 88, 74));
    title.setOutlineColor(sf::Color::Black);
    title.setStyle(sf::Text::Bold);
    title.setString("SOKOBAN");

    sf::FloatRect rect = title.getGlobalBounds();
    float posx_title = WINDOW_WIDTH / 2.0f - rect.width / 2.0f;
    float posy_title = (WINDOW_HEIGHT / 2.0f - rect.height / 2.0f) / (MAX_NUMBER_OF_ITEMS + 4) * 1.5f;
    title.setPosition(posx_title, posy_title);
    
    std::string string[MAX_NUMBER_OF_ITEMS] = { "NEW GAME", "CONTINUE", "EXIT" };
    sf::Color color = sf::Color::White;
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
        setOption(i, color, string[i]);

}

void Menu::setOption(int opt_num, sf::Color& color, const std::string& string)
{
    options[opt_num].setFont(font);
    options[opt_num].setFillColor(color);
    options[opt_num].setOutlineColor(sf::Color::Black);
    options[opt_num].setCharacterSize(50);
    options[opt_num].setString(string);

    sf::FloatRect rect = options[opt_num].getGlobalBounds();

    float posx = WINDOW_WIDTH / 2.0f -  rect.width / 2;
    float posy = WINDOW_HEIGHT / 2.0f - rect.height / 2;
    options[opt_num].setStyle(sf::Text::Bold);
    options[opt_num].setPosition(sf::Vector2f(posx, WINDOW_HEIGHT / (MAX_NUMBER_OF_ITEMS + 2.0) * (opt_num + 2)));
}

bool Menu::processEvent(sf::Event& event)
{
    bool res = false;
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
    {
        if (event.type == sf::Event::MouseButtonReleased)
        {
            sf::FloatRect rect = options[i].getGlobalBounds();
            if (rect.contains(event.mouseButton.x, event.mouseButton.y))
            {
                selectedItemIndex = i;
                res = true;
            }
        }
        else if (event.type == sf::Event::MouseMoved)
        {
            sf::FloatRect rect = options[i].getGlobalBounds();
            int old_selectedItemIndex = selectedItemIndex;

            const sf::Vector2f mouse_pos(event.mouseMove.x, event.mouseMove.y);
            if (rect.contains(mouse_pos))
                selectedItemIndex = i;
            if (selectedItemIndex != -1 && old_selectedItemIndex == -1)
                options[selectedItemIndex].setFillColor(sf::Color::Yellow);
            else if (old_selectedItemIndex != selectedItemIndex)
            {
                options[old_selectedItemIndex].setFillColor(sf::Color::White);
                options[selectedItemIndex].setFillColor(sf::Color::Yellow);
            }
        }
    }
    return res;
}

void Menu::draw(sf::RenderWindow& window)
{
    window.draw(title);

    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
        window.draw(options[i]);
}

int Menu::run()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Sokoban Menu");

    int opt = -1;
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
            if (event.type == sf::Event::Closed)
                window.close();
            else if (processEvent(event) == true)
            {
                opt = selectedItemIndex;
                window.close();
            }
		}

		window.clear(sf::Color(55, 138, 138, 1));

		draw(window);

		window.display();
	}

    return opt;
}