#include "GameObject.h"

#include <iostream>
#include <unordered_map>
#include <memory>
#include <utility>

#include "Animation/Animation.h"
#include "Animation/AnimationUnit.hpp"

#include "Interface/Interface.h"
#include "Interface/interfaceSprite.h"



GameObject::GameObject(const float &x, const float &y, const sf::Sprite& sprite, const sf::Vector2f &size, const int &priority) : interface{std::make_unique<InterfaceSprite>(sprite, priority)}, position{sf::Vector2f{x,y}}, angle{}, size{size} 
{
	interface->set_position(position);
	interface->set_angle(angle);
	interface->set_size(size);
}
GameObject::GameObject(const sf::Vector2f &position, const sf::Sprite &sprite, const sf::Vector2f &size, const int &priority) : GameObject{position.x, position.y, sprite, size, priority } {}

GameObject::GameObject(std::unique_ptr<Interface> &&interface) : interface{ std::move(interface) }, position{ this->interface->get_position() }, angle{ this->interface->get_angle() }, size{ this->interface->get_size() }
{ }

sf::Vector2f GameObject::get_position() const
{
	return position;
}

int GameObject::get_priority() const 
{
	return interface->get_priority();
}

sf::Vector2f GameObject::get_size() const
{
	return interface->get_size();
}

Interface *GameObject::get_interface() const { return interface.get(); }


void GameObject::move(const float &dx, const float &dy)
{
	position = position + sf::Vector2f{ dx, dy };
}

void GameObject::move(const sf::Vector2i &dp)
{
	position = position + sf::Vector2f{ dp };
}

void GameObject::set_position(const float &x, const float &y)
{
	position = sf::Vector2f{ x,y };
}

void GameObject::set_position(const sf::Vector2f &new_position)
{
	position = (new_position);
}

void GameObject::set_position(const sf::Vector2i &new_position)
{

	position = (sf::Vector2f{ new_position });
}

void GameObject::set_priority(const int &prio) { interface->set_priority(prio); }

void GameObject::update(sf::RenderWindow &mWindow, const float &deltaSec)
{
	if (active)
	{
		interface->set_position(position);
		interface->set_angle(angle);
		interface->set_size(size);

		for (auto &var : animations)
		{
			var.second->progress(deltaSec);
		}

		interface->display(mWindow);
		_update(mWindow, deltaSec);
	}
}


void GameObject::add_animation(std::unique_ptr<Animation> animation, std::string_view animation_name)
{
	animations.emplace(animation_name, std::move(animation));
}

void GameObject::play_animation(std::string_view animation_name)
{
	animations.at(animation_name)->play();
}

void GameObject::set_size(const float &scale) { interface->set_size(scale); }
void GameObject::set_size(const sf::Vector2f &scale) { interface->set_size(scale); }

void GameObject::activate()
{
	active = true;
}

void GameObject::desactivate()
{
	active = false;
}