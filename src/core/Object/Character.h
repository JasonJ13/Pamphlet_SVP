#pragma once

#include "GameObject.h"

#include <memory>

#include "Parchemin.h"
#include "../TextureGestioner.h"


static constexpr float duration_walking = 3;

class Character : public GameObject
{
private :
	float Timer_get_in = duration_walking;
	std::shared_ptr<Parchemin> parchemin;

	void _update(sf::RenderWindow &mWindow, const float &deltaSec) override;

	static std::shared_ptr<Parchemin> create_parchemin(TextureGestioner &textureGestioner, sf::Vector2f position);


public :
	Character(const sf::Vector2f &position, TextureGestioner &textureGestioner);

	std::shared_ptr<Parchemin> get_parchemin() const;

	
};