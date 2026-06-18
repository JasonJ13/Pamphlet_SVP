
#include <iostream>

#include "GameObject.h"
#include "Animation.hpp"



GameObject::GameObject(const float &x, const float &y, const sf::Sprite& sprite, const sf::Vector2f &size) : priority{ 0 }, sprite{ sprite }, position{sf::Vector2f{x,y}}, angle{}, size{size}
{
	/*Animation<float> animation{&position.x ,(SIZE_X / 2.f - 128), 3, false};
	Animation<float> animation2{ &position.y , position.y - 16, 0.2, true };
	Animation<float> animation3{ &position.y , position.y - 16, 0.8, true };
	animation.play();
	animation2.play();
	animations.push_back(std::move(animation));
	animations.push_back(std::move(animation2));*/
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
		std::visit([&](auto &animation){ animation.progress(deltaSec); }, var.second);
	}

	mWindow.draw(sprite);
}

void GameObject::add_animation(AnimationVariant animation, const std::string_view& animation_name, const bool play)
{
	if (play) std::visit([&](auto &anim) { anim.play(); }, animation);
	animations.emplace(animation_name, std::move(animation));
}

void GameObject::create_animation_position_x(float vend, float duration, std::string_view animation_name, bool play, bool cycle, bool reverse)
{
	Animation<float> animation{ &position.x, vend, duration, cycle, reverse };
	add_animation((AnimationVariant) animation, animation_name, play);
}

void GameObject::create_animation_position_y(float vend, float duration, std::string_view animation_name, bool play, bool cycle, bool reverse)
{
	Animation<float> animation{ &position.y, vend, duration, cycle, reverse };
	add_animation((AnimationVariant) animation, animation_name, play);
}

void GameObject::create_animation_position(sf::Vector2f vend, float duration, std::string_view animation_name, bool play, bool cycle, bool reverse)
{
	Animation<sf::Vector2f> animation{ &position, vend, duration, cycle, reverse };
	add_animation((AnimationVariant) animation, animation_name, play);
}

void GameObject::create_animation_angle(sf::Angle vend, float duration, std::string_view animation_name, bool play, bool cycle, bool reverse)
{
	Animation<sf::Angle> animation{ &angle, vend, duration, cycle, reverse };
	add_animation((AnimationVariant) animation, animation_name, play);
}

void GameObject::create_animation_size(sf::Vector2f vend, float duration, std::string_view animation_name, bool play, bool cycle, bool reverse)
{
	Animation<sf::Vector2f> animation{ &size, vend, duration, cycle, reverse };
	add_animation((AnimationVariant) animation, animation_name, play);
}