
#include "InterfaceRectangle.h"
#include "Interface.h"

#include <iostream>

InterfaceRectangle::InterfaceRectangle(const sf::Vector2f &size, const sf::Color &color, const int &priority) : rectangle{ sf::RectangleShape{} }, Interface{ priority }
{
	rectangle.setFillColor(color);
	rectangle.setSize(size);
}

InterfaceRectangle::InterfaceRectangle(const int &x, const int &y, const sf::Color &color, const int &priority) : InterfaceRectangle{sf::Vector2f(x,y), color, priority} {}


sf::Vector2f InterfaceRectangle::_get_position() const { return rectangle.getPosition(); }
sf::Angle InterfaceRectangle::_get_angle() const { return rectangle.getRotation(); }
sf::Vector2f InterfaceRectangle::_get_size() const { return rectangle.getSize(); }

void InterfaceRectangle::_set_position(const sf::Vector2f &position) { rectangle.setPosition(position); }
void InterfaceRectangle::_set_angle(const sf::Angle &angle) { rectangle.setRotation(angle); }
void InterfaceRectangle::_set_size(const sf::Vector2f &size) { rectangle.setSize(size); }

void InterfaceRectangle::_display(sf::RenderWindow &window) const {window.draw(rectangle); }