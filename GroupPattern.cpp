#include "GroupPattern.h"

//============== iComposite ==============
int iComposite::nested_ = 0;
void iComposite::addToGroup(iComponent* _component) 
{
    this->children_.push_back(_component);
    _component->setParent(this);
    calculateSize();
    initiation();
}
void iComposite::removeFromGroup(iComponent* _component) 
{
    children_.remove(_component);
    _component->setParent(nullptr);
    calculateSize();
    initiation();
}


std::string iComposite::getNest()
{
    if (nested_ < 0) nested_ = 0;
    std::string  str(nested_, '+');
    return str;
}

//============== eGroupCreator ==============
eGroupCreator::eGroupCreator()
{
    initiation();
}
eGroupCreator::eGroupCreator(const eGroupCreator& that)
{
    groupProperty = that.groupProperty;
    groupCoords = that.groupCoords;
    outLineColor_ = that.outLineColor_;
    children_.resize(that.children_.size());
    auto thisShape = children_.begin();
    for (const iComponent* shape : that.children_)
    {
        *thisShape = shape->clone();
        ++thisShape;
    }
    parent_ = that.parent_;
    initiation();
}
eGroupCreator::eGroupCreator(sf::Color _outline)
{
    outLineColor_ = _outline;
    initiation();
}

std::string eGroupCreator::getDescription()
{
    ++nested_;
    std::string result = "Group (" + std::to_string(int(groupCoords.x_)) + "," + std::to_string(int(groupCoords.y_)) +
						 "), W*H = " + std::to_string(int(groupProperty.width_)) + "*" + std::to_string(int(groupProperty.height_))
					   + ", " + color_to_string(outLineColor_) + "\n";

    for (iComponent* var : children_)
        result += getNest() + var->getDescription();

    --nested_;
    return result;
}

void eGroupCreator::draw(sf::RenderWindow& _window) const
{
    _window.draw(*this);
    for (const iComponent* shape : children_)
        shape->draw(_window);
}

void eGroupCreator::moveTo(float _x, float _y)
{
    groupCoords.x_ += _x;
    groupCoords.y_ += _y;
    for (iComponent* shape : children_)
    {
        shape->moveTo(_x, _y);
    }
}

void eGroupCreator::initiation()
{
    eInheritedShape::setSize(sf::Vector2f(groupProperty.width_, groupProperty.height_));
    eInheritedShape::setFillColor(sf::Color::White);
    eInheritedShape::setPosition(groupCoords.x_, groupCoords.y_);
    eInheritedShape::setOutlineThickness(3.f);
    eInheritedShape::setOutlineColor(outLineColor_);
}

void eGroupCreator::calculateSize()
{
    std::vector<eCoordinates> coordinates;
    std::vector<e2Dimension> properties;
    for (const iComponent* var : children_)
    {
        coordinates.push_back(var->getShapeCoords());
        properties.push_back(var->getShapeData());
    }

    float min_x = 100000;
    float min_y = 100000;
    float max_x = 0;
    float max_y = 0;
    for (size_t i = 0; i < coordinates.size(); ++i)
    {
        if (coordinates.at(i).x_ < min_x && coordinates.at(i).x_ >= 0)
            min_x = coordinates.at(i).x_;
        if (coordinates.at(i).y_ < min_y && coordinates.at(i).y_ >= 0)
            min_y = coordinates.at(i).y_;

        if (properties.at(i).radius_ == -1)
        {
            if (coordinates.at(i).x_ + properties.at(i).width_ > max_x && coordinates.at(i).x_ >= 0)
                max_x = coordinates.at(i).x_ + properties.at(i).width_;
            if (coordinates.at(i).y_ + properties.at(i).height_ > max_y && coordinates.at(i).y_ >= 0)
                max_y = coordinates.at(i).y_ + properties.at(i).height_;
        }
        else
        {
            if (coordinates.at(i).x_ + properties.at(i).radius_ * 2 > max_x && coordinates.at(i).x_ >= 0)
                max_x = coordinates.at(i).x_ + properties.at(i).radius_ * 2;
            if (coordinates.at(i).y_ + properties.at(i).radius_ * 2 > max_y && coordinates.at(i).y_ >= 0)
                max_y = coordinates.at(i).y_ + properties.at(i).radius_ * 2;
        }
    }
    groupCoords.x_ = min_x;
    groupCoords.y_ = min_y;
    groupProperty.width_ = max_x - min_x;
    groupProperty.height_ = max_y - min_y;
}


//============== Interface ==============

void Interface::DrawShapes(const std::vector<iComponent*>& _shapes)
{
    using namespace sf;
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "");

    Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color());

        for (auto shape : _shapes)
        {
            shape->draw(window);
        }
        window.display();
    }
}
void Interface::DrawShapes(const iComponent* _shape)
{
    using namespace sf;
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "");

    Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color());

    	_shape->draw(window);

        window.display();
    }
}

void Interface::printDescription(iComponent* component_)
{
    std::cout << component_->getDescription() << std::endl;
}
void Interface::printDescription(const std::vector<iComponent*>& _shapes)
{
    for (auto shape : _shapes)
        std::cout << shape->getDescription() << std::endl;
}
std::vector<iComponent*>  Interface::mergeShapes(int howManyShapes, iComponent* shape, ...)
{
    std::vector<iComponent*> shapes;
    va_list args;
    va_start(args, howManyShapes);

    while (howManyShapes--)
        shapes.push_back(va_arg(args, iComponent*));

    va_end(args);
    return shapes;
}
