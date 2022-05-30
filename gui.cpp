#include "gui.h"

// Implementation of Widget class
void Widget::updateShape()
{
    if (_parent)
        _parent.updateShape();
}

void Widget::setPosition(float x, float y)
{
    _position.x = x;
    _position.y = y;
}