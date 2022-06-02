#ifndef BUTTON_H_
#define BUTTON_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Button : public sf::Drawable
{
    private:
        enum Status { None = 0, Hover = 1 };
        int _status;
        sf::Vector2f _position;
        sf::RectangleShape _shape;
        sf::Font _font;
        sf::Text _label;
        sf::Color _fillColor;
        sf::Color _outlineColor;

        void updateShape();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        void onMouseEntered();
        void onMouseLeft();
        
    public:
        Button(const std::string& text);
        ~Button() {};

        void setPosition(const sf::Vector2f& pos) { _position = pos; }
        void setPosition(float x, float y) { _position = sf::Vector2f(x, y); }
        const sf::Vector2f& getPosition() const { return _position; }
        sf::Vector2f getSize() const;

        void setText(const std::string& text);
        void setCharacterSize(unsigned int size);

        void setTextColor(const sf::Color& color) { _label.setFillColor(color); }
        void setFillColor(const sf::Color& color);
        void setOutlineColor(const sf::Color& color);
        void setOutlineThickness(float thickness) { _shape.setOutlineThickness(thickness); }

        bool processEvent(const sf::Event& event);
};

#endif