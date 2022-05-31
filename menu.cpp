#include <iostream>
#include "menu.h"
#include "constant.h"

Menu::Menu(): selectedItemIndex(0)
{
    if (!font.loadFromFile("assets/font/arial.ttf"))
    {
        std::cout << "font can't be loaded!\n";
    }

    std::string string[MAX_NUMBER_OF_ITEMS] = { "PLAY", "INSTRUCTION", "EXIT" };
    sf::Color color = sf::Color::White;
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
        setOption(i, color, string[i]);

}

void Menu::setOption(int opt_num, sf::Color& color, const std::string& string)
{
    options[opt_num].setFont(font);
    options[opt_num].setFillColor(color);
    options[opt_num].setOutlineColor(color);
    options[opt_num].setString(string);

    sf::FloatRect rect = options[opt_num].getGlobalBounds();

    float posx = WINDOW_WIDTH / 2.0f -  rect.width / 2;
    float posy = WINDOW_HEIGHT / 2.0f - rect.height / 2;
    options[opt_num].setStyle(sf::Text::Bold);
    options[opt_num].setPosition(sf::Vector2f(posx, WINDOW_HEIGHT / (MAX_NUMBER_OF_ITEMS + 1.0) * (opt_num + 1)));
}

void Menu::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
        window.draw(options[i]);
}

void Menu::moveUp()
{
    if (selectedItemIndex - 1 >= 0)
    {
        options[selectedItemIndex].setFillColor(sf::Color::White);
        options[selectedItemIndex].setOutlineColor(sf::Color::White);

        selectedItemIndex--;
        options[selectedItemIndex].setFillColor(sf::Color::Red);
        options[selectedItemIndex].setOutlineColor(sf::Color::Red);
    }
}

void Menu::moveDown()
{
    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
    {
        options[selectedItemIndex].setFillColor(sf::Color::White);
        options[selectedItemIndex].setOutlineColor(sf::Color::White);
        selectedItemIndex++;
        options[selectedItemIndex].setFillColor(sf::Color::Red);
        options[selectedItemIndex].setOutlineColor(sf::Color::Red);
    }
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
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					moveUp();
					break;

				case sf::Keyboard::Down:
					moveDown();
					break;

				case sf::Keyboard::Return:
					// switch (GetPressedItem())
					// {
					// case 0:
					// 	std::cout << "Play button has been pressed" << std::endl;
					// 	break;
					// case 1:
					// 	std::cout << "Option button has been pressed" << std::endl;
					// 	break;
					// case 2:
					// 	window.close();
					// 	break;
					// }
                    if (GetPressedItem() <= 2)
                    {
                        opt = GetPressedItem();
                        window.close();
                    }

					break;
				}

				break;
			case sf::Event::Closed:
				window.close();

				break;

			}
		}

		window.clear(sf::Color(55, 138, 138, 1));

		draw(window);

		window.display();
	}

    return opt;
}