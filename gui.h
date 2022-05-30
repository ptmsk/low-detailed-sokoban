#ifndef GUI_H_
#define GUI_H_

#include <SFML/Graphics.hpp>

class Widget : public Drawable
{
    protected:
        Widget* _parent;
        sf::Vector2f _position;

        virtual bool processEvent(const sf::Event& event, const sf::Vector2f& parent_pos) { return false; }
        virtual bool processEvent(const sf::Vector2f& parent_pos) {}
        virtual void updateShape();

    public:
        Widget(Widget* parent=NUL) _parent(parent) {}
        virtual ~Widget() {}

        void setPosition(const sf::Vector2f& pos) { _position = pos; }
        void setPosition(float x, float y);
        const sf::Vector2f& getPosition() const { return _position; }
        virtual sf::Vector2f getSize() const = 0;
}

#endif