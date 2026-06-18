#pragma once

#include "GameObject.h"
#include "../TextureGestioner.h"

class Character : public GameObject
{


public :
	Character(sf::Vector2f position, TextureGestioner &textureGestioner);
};