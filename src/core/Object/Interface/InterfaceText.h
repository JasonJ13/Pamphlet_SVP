#pragma once

#include "Interface.h"

#include <SFML/Graphics.hpp>
#include <string_view>

static sf::Font font{ "resources/Garamontio.ttf" };

class InterfaceText : public Interface
{
private :
	sf::Text text;

	sf::Vector2f _get_position() const override;
	sf::Angle _get_angle() const override;
	sf::Vector2f _get_size() const override;

	void _set_position(const sf::Vector2f &position) override;
	void _set_angle(const sf::Angle &angle) override;
	void _set_size(const sf::Vector2f &size) override;
	

	void _display(sf::RenderWindow &window) const override;


public :
	InterfaceText(const std::string &string, const int &priority = 0);
	void set_string(const std::string &string);
};
