#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "GroupPattern.h"

class iShape : public iComponent
{
public:
    virtual ~iShape() override = default;
    iShape() = default;
    iShape(float _x, float _y);
    iShape(eCoordinates _coord, sf::Color _color);
    iShape(const iShape& that);

    void moveTo(float _x, float _y) final;

    iComponent* clone() const override = 0;

    std::string getDescription() = 0;
    virtual void draw(sf::RenderWindow& _window) const = 0;
protected:
    eCoordinates shapeCoords = eCoordinates(1, 1);
    sf::Color colour_ = sf::Color::Cyan;
protected:
    eCoordinates getShapeCoords() const final { return shapeCoords; }
    e2Dimension getShapeData() const = 0;
    virtual void initiation() = 0;
};


class eRectangleShape : public iShape,
    public sf::RectangleShape
{
    using eInheritedPattern = iShape;
    using eInheritedShape = sf::RectangleShape;
public:
    virtual ~eRectangleShape() override = default;
    eRectangleShape();
    eRectangleShape(float _x, float _y, float _width, float _height);
    eRectangleShape(const eRectangleShape& that) ;
    eRectangleShape(sf::Color);
    eRectangleShape(float _x, float _y);
    eRectangleShape(e2Dimension _size);
    eRectangleShape(eCoordinates _coord);
    eRectangleShape(e2Dimension _size, eCoordinates _coord, sf::Color);
    eRectangleShape(e2Dimension _size, eCoordinates _coord);

    std::string getDescription()  override;
    void draw(sf::RenderWindow& _window) const override;

    iComponent* clone() const override { return new eRectangleShape(*this); }
protected:
    e2Dimension shapeProperty = e2Dimension(1, 1);
    std::string name_ = "Rectangle";
protected:
    e2Dimension getShapeData() const override { return shapeProperty; }
    void initiation() override;
};


class eCircleShape : public iShape
				   , public sf::CircleShape
{
    using eInheritedPattern = iShape;
    using eInheritedShape = sf::CircleShape;
public:
    virtual ~eCircleShape() override = default;
    eCircleShape();
    eCircleShape(const eCircleShape& that);
    eCircleShape(float _x, float _y);
    eCircleShape(float _x, float _y, float _radius);
    eCircleShape(float _x, float _y, sf::Color _color);
    eCircleShape(eCoordinates _coord, float _radius, sf::Color _color);

    std::string getDescription()  override;
    void draw(sf::RenderWindow& _window) const override;

    iComponent* clone() const override { return new eCircleShape(*this); }
protected:
    e2Dimension shapeProperty = e2Dimension(1);
    std::string name_ = "Circle";
protected:
    e2Dimension getShapeData() const override { return shapeProperty; }
    void initiation() override;
};

