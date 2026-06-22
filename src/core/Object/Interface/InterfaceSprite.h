#pragma once

#include "Interface.h"

#include <SFML/Graphics.hpp>
#include <string_view>

#include "../../TextureGestioner.h"

class InterfaceSprite : public Interface
{
private :
	sf::Sprite sprite;

	sf::Vector2f _get_position() const override;
	sf::Angle _get_angle() const override;
	sf::Vector2f _get_size() const override;

	void _set_position(const sf::Vector2f &position) override;
	void _set_angle(const sf::Angle &angle) override;
	void _set_size(const sf::Vector2f &size) override;

	void _display(sf::RenderWindow &window) const override;

public :
	InterfaceSprite(const std::string_view &file_name, TextureGestioner &texturegestioner, const int &priority = 0, const float &scale = 1);
	InterfaceSprite(const sf::Sprite &sprite, const int &priority = 0);

};