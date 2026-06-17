
#include <iostream>

#include "GameObject.h"
#include "Animation.hpp"
#include "Game.h"


GameObject::GameObject(const float &x, const float &y, const sf::Sprite& sprite, const sf::Vector2f &size) : priority{ 0 }, sprite{ sprite }, position{sf::Vector2f{x,y}}, angle{}
{
	this->sprite.setScale(size);


	Animation<float> animation{ &position.x ,(SIZE_X / 2.f - 128), 3, false};
	Animation<float> animation2{ &position.y , position.y - 16, 0.2, true };
	Animation<float> animation3{ &position.y , position.y - 16, 0.8, true };
	animation.play();
	animation2.play();
	animations.push_back(std::move(animation));
	animations.push_back(std::move(animation2));

}
GameObject::GameObject(const sf::Vector2f &position, const sf::Sprite &sprite, const sf::Vector2f &size) : GameObject{position.x, position.y, sprite, size } {}


sf::Vector2f GameObject::get_position() const
{
	return position;
}

int GameObject::get_priority() const 
{
	return priority;
}


void GameObject::move(float dx, float dy)
{
	position = position + sf::Vector2f{ dx, dy };
}

void GameObject::move(sf::Vector2i dp)
{
	position = position + sf::Vector2f{ dp };
}

void GameObject::set_position(float x, float y)
{
	position = position + sf::Vector2f{ x,y };
}

void GameObject::set_position(sf::Vector2f new_position)
{
	position = (new_position);
}

void GameObject::set_position(sf::Vector2i new_position)
{

	position = (sf::Vector2f{ new_position });
}


void GameObject::display(sf::RenderWindow &mWindow, float deltaSec)
{
	sprite.setPosition(position);
	sprite.setRotation(angle);

	for (auto &var : animations)
	{
		std::visit([&](auto &animation){ animation.progress(deltaSec); }, var);
	}

	mWindow.draw(sprite);
}