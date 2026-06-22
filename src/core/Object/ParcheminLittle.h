#pragma once

#include "Object/InteractibleObject.h"
#include "../TextureGestioner.h"

class ParcheminLittle : public InteractibleObject
{

private :
	void _grabed(const sf::Vector2i &mouse_position) override;
	void _hold(const sf::Vector2i &mouse_position) override;
	void _release(const sf::Vector2i &mouse_position, const sf::Vector2f &last_position = sf::Vector2f{}) override;

	void _update(sf::RenderWindow &mWindow, const float &deltaSec) override;

public :
	ParcheminLittle(const sf::Vector2f &position, TextureGestioner &textureGestioner);
};
