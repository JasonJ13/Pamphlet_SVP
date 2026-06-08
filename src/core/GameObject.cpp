
#include <iostream>

#include "GameObject.h"


GameObject::GameObject(const float &x, const float &y, const std::string_view &sprite_name) : priority{ 0 }, texture{}, sprite(texture)
{
	if (texture.loadFromFile(std::string(sprite_name))) 
	{
		sprite.setPosition(sf::Vector2f(x, y));
	  sprite.setTexture(texture, true);
	}
	else
	{
		std::cout << "L'image n'a pas pu etre charge" << std::endl;
	}
	return;
}


void GameObject::move(float dx, float dy)
{
	sprite.setPosition(sprite.getPosition() + sf::Vector2f{ dx, dy });
}

void GameObject::move(sf::Vector2i dp)
{
	sprite.setPosition(sprite.getPosition() + sf::Vector2f{ dp });
}

void GameObject::set_position(float x, float y)
{
	sprite.setPosition(sf::Vector2f{ x,y });
}

void GameObject::set_position(sf::Vector2f new_position)
{
	sprite.setPosition(new_position);
}

void GameObject::set_position(sf::Vector2i new_position)
{
	sprite.setPosition(sf::Vector2f{ new_position });
}


void GameObject::display(sf::RenderWindow &mWindow) const
{
	mWindow.draw(sprite);
}