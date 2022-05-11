#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <list>
#include <vector>
#include <string>
#include <chrono>
#include <stdarg.h>
#include <iostream>


const uint32_t WINDOW_WIDTH = 1200;
const uint32_t WINDOW_HEIGHT = 800;

struct eCoordinates
{
    eCoordinates() = default;
	eCoordinates(float _x, float _y): x_(_x), y_(_y) {}
    float x_ = -1;
    float y_ = -1;
};
struct e2Dimension
{
    e2Dimension() = default;
    e2Dimension(float _height, float _weight) : width_(_weight), height_(_height) {}
    e2Dimension(float _radius) : radius_(_radius) {}

	float width_ = -1;
    float height_ = -1;
    float radius_ = -1;
};
struct eColor
{
    eColor() = default;
    eColor(sf::Color _color) : color_(_color) { }

    sf::Color color_ = sf::Color::Cyan;
};
class Timer
{
public:
    Timer() : m_beg(clock_t::now()){}

    void reset() { m_beg = clock_t::now(); }

    double elapsed() const { return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count(); }
private:
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;

    std::chrono::time_point<clock_t> m_beg;
};

inline std::string color_to_string(const sf::Color& color)
{
    if (color == sf::Color::Cyan)
        return "Cyan";
    if (color == sf::Color::Red)
        return "Red";
    if (color == sf::Color::White)
        return "White";
    if (color == sf::Color::Black)
        return "Black";
    if (color == sf::Color::Blue)
        return "Blue";
    if (color == sf::Color::Green)
        return "Green";
    if (color == sf::Color::Magenta)
        return "Magenta";
    if (color == sf::Color::Yellow)
        return "Yellow";
    else
        return "None";
}

class iComponent
{
public:
    virtual ~iComponent() = default;


    virtual void addToGroup(iComponent* _component) {}
    virtual void removeFromGroup(iComponent* _component) {}

    virtual std::string getDescription() = 0;
    virtual void moveTo(float _x, float _y) = 0;

    void setParent(iComponent* _parent) { this->parent_ = _parent; }
    virtual iComponent* clone() const = 0;


    virtual void draw(sf::RenderWindow& _window) const = 0;

    virtual eCoordinates getShapeCoords() const = 0;
    virtual e2Dimension getShapeData() const = 0;
protected:
    iComponent* parent_;
};


class iComposite : public iComponent
{
public:
    virtual ~iComposite() override = default;


    std::string getDescription() override = 0;

    void moveTo(float _x, float _y) override = 0;

    void addToGroup(iComponent* _component) override;
    void removeFromGroup(iComponent* _component) override;

    iComponent* clone() const override = 0;
    virtual void draw(sf::RenderWindow& _window) const override = 0;

protected:
    std::list<iComponent*> children_;
    static int nested_;
protected:
    static std::string getNest();

    eCoordinates getShapeCoords() const override = 0;
    e2Dimension getShapeData() const override = 0;

    virtual void calculateSize() = 0;
    virtual void initiation() = 0;
};

class eGroupCreator : public iComposite
					, public sf::RectangleShape
{
    using eInheritedPattern = iComposite;
    using eInheritedShape = sf::RectangleShape;
public:
    virtual ~eGroupCreator() override = default;

    eGroupCreator();
    eGroupCreator(sf::Color _outline);
    eGroupCreator(const eGroupCreator& that);

    void moveTo(float _x, float _y) override;

    std::string getDescription() override;
    void draw(sf::RenderWindow& _window) const override;

    iComponent* clone() const override { return new eGroupCreator(*this); }
protected:
    eCoordinates groupCoords = eCoordinates(0, 0);
    e2Dimension groupProperty = e2Dimension(0,0);
    sf::Color outLineColor_ = sf::Color::Red;
protected:
    void initiation();
    void calculateSize() override;

    eCoordinates getShapeCoords() const override { return groupCoords; }
    e2Dimension getShapeData() const override { return groupProperty; }
};


class Interface
{
public:
    static void DrawShapes(const std::vector<iComponent*>& _shapes);
    static void DrawShapes(const iComponent* _shape);

    static void  printDescription(iComponent* component_);

    static void  printDescription(const std::vector<iComponent*>& _shapes);

    static std::vector<iComponent*> mergeShapes(int howManyShapes, iComponent* shape, ...);
};