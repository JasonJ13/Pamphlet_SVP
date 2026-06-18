
#include <iostream>

#include "InteractibleObject.h"


InteractibleObject::InteractibleObject(const float &x, const float &y, const sf::Sprite &sprite, const sf::Vector2f &size) : GameObject{ x, y, sprite, size }, hitbox { x, y, 0, 0 }, offset{ 0, 0 }
{
	hitbox.sizeX = 128;
	hitbox.sizeY = 128;
}
InteractibleObject::InteractibleObject(const sf::Vector2f &position, const sf::Sprite &sprite, const sf::Vector2f &size) : InteractibleObject{position.x, position.y, sprite, size} {}



bool InteractibleObject::is_hit(sf::Vector2i position_object) const
{
	auto position = get_position();
	if (position_object.x < position.x || position_object.x > position.x + hitbox.sizeX)
	{
		return false;
	}
	if (position_object.y < position.y || position_object.y > position.y + hitbox.sizeY)
	{
		return false;
	}
	return true;
}

void InteractibleObject::grabed(sf::Vector2i mouse_position)
{
	sf::Vector2f position = get_position();
	offset.x = mouse_position.x - position.x;
	offset.y = mouse_position.y - position.y;
}


void InteractibleObject::set_position(float x, float y)
{
	GameObject::set_position(x - offset.x, y - offset.y);
}

void InteractibleObject::set_position(sf::Vector2f new_position)
{
	GameObject::set_position(new_position - sf::Vector2f( offset.x,offset.y ));
}

void InteractibleObject::set_position(sf::Vector2i new_position)
{
	GameObject::set_position(new_position - offset);
}