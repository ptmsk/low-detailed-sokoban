#include "button.h"

Button::Button(const std::string& text): _status(Status::None)
{
    _font.loadFromFile("assets/font/arial.ttf");
    _label.setFont(_font);
    setText(text);
    setCharacterSize(20);
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
    sf::FloatRect label_rect = _label.getGlobalBounds();
    sf::Vector2f label_size = sf::Vector2f(label_rect.width, label_rect.height);
    unsigned int char_size = _label.getCharacterSize();

    _shape.setSize(sf::Vector2f(2*char_size + label_size.x, 2*char_size + label_size.y));
    _label.setPosition(char_size, char_size);
}

bool Button::processEvent(const sf::Event& event)
{
    bool res = false;
    if (event.type == sf::Event::MouseButtonReleased)
    {
        // const sf::Vector2f pos = _position;
        const sf::Vector2f size = getSize();
        sf::FloatRect rect;
        rect.left = _position.x;
        rect.top = _position.y;
        rect.width = size.x;
        rect.height = size.y;

        if (rect.contains(event.mouseButton.x, event.mouseButton.y))
        {
            // onClick(event, *this);
            res = true;
        }
    }
    else if (event.type == sf::Event::MouseMoved)
    {
        // const sf::Vector2f pos = _position + parent_pos;
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
        if ((old_status && Status::Hover) && not (_status && Status::Hover))
            onMouseLeft();
        else if (not (old_status && Status::Hover) && (_status && Status::Hover))
            onMouseEntered();
    }

    return res;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform.translate(_position);
    target.draw(_shape, states);
    // target.draw(_label, states);
}

void Button::onMouseEntered()
{
    const float light = 1.4f;
    _shape.setOutlineColor(sf::Color(_outlineColor.r * light, _outlineColor.g * light, _outlineColor.b * light));
    _shape.setFillColor(sf::Color(_fillColor.r * light, _fillColor.g * light, _fillColor.b * light));
}

void Button::onMouseLeft()
{
    _shape.setOutlineColor(_outlineColor);
    _shape.setFillColor(_fillColor);
}