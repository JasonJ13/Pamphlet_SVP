#pragma once

#include "GameObject.h"
#include "Interface/Interface.h"

#include <string_view>

#include "../TextureGestioner.h"

class FixObject : public GameObject
{
private :
	void _update(sf::RenderWindow &mWindow, const float &deltaSec) override;

public:
	FixObject(const float &x, const float &y, const std::string_view &sprite_name, TextureGestioner& textureGestioner, const sf::Vector2f &size = sf::Vector2f{ 1, 1 }, const int &priority = 0);
	FixObject(const sf::Vector2f &position, const std::string_view &sprite_name, TextureGestioner& textureGestioner, const sf::Vector2f &size = sf::Vector2f{ 1, 1 }, const int &priority = 0);

	FixObject(std::unique_ptr<Interface> &&interface);
};