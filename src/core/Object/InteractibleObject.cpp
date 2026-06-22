#include "InteractibleObject.h"

#include "Interface/Interface.h"	

#include <iostream>

InteractibleObject::InteractibleObject(const float &x, const float &y, const sf::Sprite &sprite, const sf::Vector2f &size, const int &priority) : GameObject{ x, y, sprite, size, priority }, hitbox { x, y, 0, 0 }, offset{ 0, 0 }
{
	hitbox.sizeX = get_size().x;
	hitbox.sizeY = get_size().y;
}
InteractibleObject::InteractibleObject(const sf::Vector2f &position, const sf::Sprite &sprite, const sf::Vector2f &size, const int &priority) : InteractibleObject{position.x, position.y, sprite, size, priority} {}

InteractibleObject::InteractibleObject(std::unique_ptr<Interface> &&interface) : GameObject{ std::move(interface) }
{
	hitbox.sizeX = get_size().x;
	hitbox.sizeY = get_size().y;
}


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


void InteractibleObject::set_hitbox_size(const sf::Vector2f &size)
{
	hitbox.sizeX = size.x;
	hitbox.sizeY = size.y;
}

void InteractibleObject::set_offset(const sf::Vector2i &position)
{
	offset = position ;
}

sf::Vector2f InteractibleObject::get_hitbox_size() const
{
	return sf::Vector2f{ hitbox.sizeX, hitbox.sizeY };
}



void InteractibleObject::set_position(const float &x, const float &y)
{

	GameObject::set_position(x - offset.x, y - offset.y);
}

void InteractibleObject::set_position(const sf::Vector2f &new_position)
{
	GameObject::set_position(new_position - sf::Vector2f( offset ));
}

void InteractibleObject::set_position(const sf::Vector2i &new_position)
{
	GameObject::set_position(new_position - offset);
}

void InteractibleObject::grabed(const sf::Vector2i &mouse_position)
{
	sf::Vector2f position = get_position();
	set_offset(mouse_position - sf::Vector2i{ position });

	_grabed(mouse_position);
}

void InteractibleObject::hold(const sf::Vector2i &mouse_position)
{
	set_position(mouse_position);

	_hold(mouse_position);
}

void InteractibleObject::release(const sf::Vector2i &mouse_position, const sf::Vector2f &last_position)
{
	_release(mouse_position, last_position);
}

