
#include "Object/InteractibleObject.h"
#include "../TextureGestioner.h"

class Parchemin : public InteractibleObject
{

public :
	Parchemin(const sf::Vector2f &position, TextureGestioner &textureGestioner);
};
