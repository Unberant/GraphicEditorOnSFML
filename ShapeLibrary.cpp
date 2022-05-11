#include "ShapeLibrary.h"

//============== iShape ==============
iShape::iShape(float _x, float _y)
{
    shapeCoords.x_ = _x;
    shapeCoords.y_ = _y;
}
iShape::iShape(eCoordinates _coord, sf::Color _color)
{
    shapeCoords.x_ = _coord.x_;
    shapeCoords.y_ = _coord.y_;
    colour_ = _color;
}
iShape::iShape(const iShape& that)
{
    shapeCoords = that.shapeCoords;
    colour_ = that.colour_;
    parent_ = that.parent_;
}

void iShape::moveTo(float _x, float _y) 
{
    shapeCoords.x_ += _x;
    shapeCoords.y_ += _y;
}

//============== eRectangleShape ==============
eRectangleShape::eRectangleShape() : iShape(eCoordinates(1, 1), sf::Color::Cyan) { initiation(); }
eRectangleShape::eRectangleShape(float _x, float _y) : iShape(_x, _y) { initiation(); }
eRectangleShape::eRectangleShape(eCoordinates _coord) : iShape(_coord.x_, _coord.y_) { initiation(); }
eRectangleShape::eRectangleShape(sf::Color _color) : iShape(eCoordinates(1, 1), _color) { initiation(); }
eRectangleShape::eRectangleShape(const eRectangleShape& that) : iShape(that)
{
    shapeProperty = that.shapeProperty;
    parent_ = that.parent_;
    initiation();
}
eRectangleShape::eRectangleShape(e2Dimension _size)
{
    shapeProperty.width_ = _size.width_;
    shapeProperty.height_ = _size.height_;
    initiation();
}
eRectangleShape::eRectangleShape(float _x, float _y, float _width, float _height) : iShape(_x, _y)
{
    shapeProperty.width_ = _width;
    shapeProperty.height_ = _height;
    initiation();
}
eRectangleShape::eRectangleShape(e2Dimension _size, eCoordinates _coord) : iShape(_coord.x_, _coord.y_)
{
    shapeProperty.width_ = _size.width_;
    shapeProperty.height_ = _size.height_;
    initiation();
}
eRectangleShape::eRectangleShape(e2Dimension _size, eCoordinates _coord, sf::Color _color) : iShape(eCoordinates(_coord.x_, _coord.y_), _color)
{
    shapeProperty.width_ = _size.width_;
    shapeProperty.height_ = _size.height_;
    initiation();
}

void eRectangleShape::draw(sf::RenderWindow& _window) const
{
    _window.draw(*this);
}
std::string eRectangleShape::getDescription()
{
    return name_ + "(" + std::to_string(int(shapeCoords.x_)) + "," + std::to_string(int(shapeCoords.y_)) + 
    		"), Color:" + color_to_string(colour_) + 
			", W*H = " + std::to_string(int(shapeProperty.width_)) + "*" + std::to_string(int(shapeProperty.height_)) + "\n";
}
void eRectangleShape::initiation()
{
    eInheritedShape::setSize(sf::Vector2f(shapeProperty.width_, shapeProperty.height_));
    eInheritedShape::setFillColor(colour_);
    eInheritedShape::setPosition(shapeCoords.x_, shapeCoords.y_);
}
//============== eCircleShape ==============
eCircleShape::eCircleShape() { initiation(); };
eCircleShape::eCircleShape(float _x, float _y) : iShape(_x, _y) { initiation(); }
eCircleShape::eCircleShape(float _x, float _y, sf::Color _color) : iShape(eCoordinates(_x, _y), _color) { initiation(); }
eCircleShape::eCircleShape(const eCircleShape& that) : iShape(that)
{
    shapeProperty = that.shapeProperty;
    //parent_ = that.parent_;
    initiation();
}
eCircleShape::eCircleShape(float _x, float _y, float _radius) : iShape(_x, _y)
{
    shapeProperty.radius_ = _radius;
    initiation();
}
eCircleShape::eCircleShape(eCoordinates _coord, float _radius, sf::Color _color) : iShape(_coord, _color)
{
    shapeProperty.radius_ = _radius;
    initiation();
}

void eCircleShape::draw(sf::RenderWindow& _window) const
{
    _window.draw(*this);
}
std::string eCircleShape::getDescription()
{
    return name_ + "(" + std::to_string(int(shapeCoords.x_)) + "," + std::to_string(int(shapeCoords.y_)) +
    		"), Color:" + color_to_string(colour_) +
			", R = " + std::to_string(int(shapeProperty.radius_)) + "\n";
}
void eCircleShape::initiation()
{
    eInheritedShape::setRadius(shapeProperty.radius_);
    eInheritedShape::setFillColor(colour_);
    eInheritedShape::setPosition(shapeCoords.x_, shapeCoords.y_);
}
