#ifndef MENU_H_
#define MENU_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#define MAX_NUMBER_OF_ITEMS 3

class Menu
{
    private:
        int selectedItemIndex;
        sf::Font font;
        sf::Text options[MAX_NUMBER_OF_ITEMS];

        void setOption(int opt_num, sf::Color& color, const std::string& string);

    public:
        Menu();
        ~Menu() {}

        void draw(sf::RenderWindow& window);
        void moveUp();
        void moveDown();
        int GetPressedItem() { return selectedItemIndex; }
        int run();

};

#endif