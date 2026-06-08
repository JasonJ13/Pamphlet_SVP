
#include "InteractibleObject.h"


InteractibleObject::InteractibleObject(const float &x, const float &y, const std::string_view &sprite_name) : GameObject{ x, y, sprite_name }, hitbox { x, y, 0, 0 }, offset{ 0, 0 }
{
	sf::vector2f scale = sprite.getScale();
	hitbox.x = scale.x;
	hitbox.y = scale.y;
}


bool InteractibleObject::is_hit(sf::Vector2i position) const
{
	if (position.x < hitbox.x || position.x > hitbox.x + hitbox.sizeX)
	{
		return false;
	}
	if (position.y < hitbox.y || position.y > hitbox.y + hitbox.sizeY)
	{
		return false;
	}

	return true;
}

void InteractibleObject::grabed(sf::Vector2i mouse_position)
{
	offset.x = mouse_position.x - x;
	offset.y = mouse_position.y - y;
}