#pragma once

#include "Interface.h"

class InterfaceRectangle : public Interface
{
private :
	sf::RectangleShape rectangle;

	sf::Vector2f _get_position() const override;
	sf::Angle _get_angle() const override;
	sf::Vector2f _get_size() const override;

	void _set_position(const sf::Vector2f &position) override;
	void _set_angle(const sf::Angle &angle) override;
	void _set_size(const sf::Vector2f &size) override;

	void _display(sf::RenderWindow &window) const override;

public :
	InterfaceRectangle(const sf::Vector2f &size, const sf::Color &color, const int &priority = 0);
	InterfaceRectangle(const int &x, const int &y, const sf::Color &color, const int &priority = 0);
};