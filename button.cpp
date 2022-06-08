#include "button.h"

Button::Button(const std::string& text, const sf::Font& font): _status(Status::None)
{
    _label.setFont(font);
    _label.setStyle(sf::Text::Bold);
    setText(text);
    setCharacterSize(30);
    setTextColor(sf::Color(180, 93, 23));

    setFillColor(sf::Color(86, 20, 19));
    setOutlineThickness(5);
    setOutlineColor(sf::Color(146, 20, 19));
}

sf::Vector2f Button::getSize() const
{
    sf::FloatRect rect = _shape.getGlobalBounds();
    return sf::Vector2f(rect.width, rect.height);
}

void Button::setText(const std::string& text)
{
    _label.setString(text);
    updateShape();
}

void Button::setCharacterSize(unsigned int size) 
{
    _label.setCharacterSize(size);
    updateShape();
}

void Button::setFillColor(const sf::Color& color)
{
    _fillColor = color;
    _shape.setFillColor(color);
}

void Button::setOutlineColor(const sf::Color& color)
{
    _outlineColor = color;
    _shape.setOutlineColor(color);
}

void Button::updateShape()
{
    // update shape when updating text
    sf::FloatRect label_rect = _label.getGlobalBounds();
    sf::Vector2f label_size = sf::Vector2f(label_rect.width, label_rect.height);
    unsigned int char_size = _label.getCharacterSize();

    _shape.setSize(sf::Vector2f(char_size + label_size.x, char_size + label_size.y));
    _label.setPosition(char_size / 2, char_size / 3);
}

bool Button::processEvent(const sf::Event& event)
{
    bool res = false;
    if (event.type == sf::Event::MouseButtonReleased)
    {
        const sf::Vector2f size = getSize();
        sf::FloatRect rect;
        rect.left = _position.x;
        rect.top = _position.y;
        rect.width = size.x;
        rect.height = size.y;

        if (rect.contains(event.mouseButton.x, event.mouseButton.y))
            res = true;
    }
    else if (event.type == sf::Event::MouseMoved)
    {
        const sf::Vector2f size = getSize();
        sf::FloatRect rect;
        rect.left = _position.x;
        rect.top = _position.y;
        rect.width = size.x;
        rect.height = size.y;
        int old_status = _status;
        _status = Status::None;

        const sf::Vector2f mouse_pos(event.mouseMove.x, event.mouseMove.y);
        if (rect.contains(mouse_pos))
            _status = Status::Hover;
        if (old_status && not (_status))
            onMouseLeft();          // Mouse leave the button
        else if (not (old_status) && _status)
            onMouseEntered();       // Mouse enter the button
    }

    return res;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform.translate(_position);
    target.draw(_shape, states);
    target.draw(_label, states);
}

void Button::onMouseEntered()
{
    // lighter color effect when Mouse is in the button
    const float light = 1.4f;
    _shape.setOutlineColor(sf::Color(_outlineColor.r * light, _outlineColor.g * light, _outlineColor.b * light));
    _shape.setFillColor(sf::Color(_fillColor.r * light, _fillColor.g * light, _fillColor.b * light));
}

void Button::onMouseLeft()
{
    // revert the button's color when Mouse leave the button
    _shape.setOutlineColor(_outlineColor);
    _shape.setFillColor(_fillColor);
}