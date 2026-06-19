
#include <iostream>
#include <unordered_map>

#include "GameObject.h"
#include "Animation/Animation.h"
#include "Animation/AnimationUnit.hpp"



GameObject::GameObject(const float &x, const float &y, const sf::Sprite& sprite, const sf::Vector2f &size) : priority{ 0 }, sprite{ sprite }, position{sf::Vector2f{x,y}}, angle{}, size{size}{}
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
	position = sf::Vector2f{ x,y };
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
	sprite.setScale(size);

	for (auto &var : animations)
	{
		var.second->progress(deltaSec);
	}

	mWindow.draw(sprite);
}


void GameObject::add_animation(std::unique_ptr<Animation> animation, std::string_view animation_name)
{
	animations.emplace(animation_name, std::move(animation));
}


void GameObject::create_animation_position_x(float vend, float duration, std::string_view animation_name, bool cycle, bool reverse)
{
	auto animation = std::make_unique<AnimationUnit<float>>(&position.x, vend, duration, cycle, reverse);
	add_animation(std::move(animation), animation_name);
}

void GameObject::create_animation_position_y(float vend, float duration, std::string_view animation_name, bool cycle, bool reverse)
{
	auto animation = std::make_unique<AnimationUnit<float>>(&position.y, vend, duration, cycle, reverse);
	add_animation(std::move(animation), animation_name);
}

void GameObject::create_animation_position(sf::Vector2f vend, float duration, std::string_view animation_name, bool cycle, bool reverse)
{
	auto animation = std::make_unique < AnimationUnit<sf::Vector2f>>(&position, vend, duration, cycle, reverse);
	add_animation(std::move(animation), animation_name);
}

void GameObject::create_animation_angle(sf::Angle vend, float duration, std::string_view animation_name, bool cycle, bool reverse)
{
	auto animation = std::make_unique<AnimationUnit<sf::Angle>>(&angle, vend, duration, cycle, reverse);
	add_animation(std::move(animation), animation_name);
}

void GameObject::create_animation_size(sf::Vector2f vend, float duration, std::string_view animation_name, bool cycle, bool reverse)
{
	auto animation = std::make_unique< AnimationUnit<sf::Vector2f>>(&size, vend, duration, cycle, reverse);
	add_animation(std::move(animation), animation_name);
}

void GameObject::play_animation(std::string_view animation_name)
{
	animations.at(animation_name)->play();
}