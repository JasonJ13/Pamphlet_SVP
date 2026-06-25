
#include "Character.h"

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <string>

#include "../Animation/AnimationUnit.hpp"
#include "../Animation/AnimationGroupLinear.h"
#include "../Animation/AnimationGroupParallel.h"

#include "../Game.h"


Character::Character(const sf::Vector2f &position, TextureGestioner &textureGestioner) : GameObject{ position, textureGestioner.load("resources/Cyrano.png"), sf::Vector2f(8,8), 4 }
{

	auto anim1 = std::make_unique<AnimationUnit<float>>(&this->position.x, SIZE_X/6 - get_size().x/2, duration_walking);
	auto anim2 = std::make_unique<AnimationUnit<float>>(&this->position.y, this->position.y + 10, 0.25, true, true);

	auto animcombine = std::make_unique<AnimationGroupParallel>(duration_walking);
	animcombine->add_Animation(std::move(anim1));
	animcombine->add_Animation(std::move(anim2));

	auto anim3 = std::make_unique<AnimationUnit<float>>(&this->position.y, this->position.y + 10, 1, true, true);

	auto animlinear = std::make_unique<AnimationGroupLinear>(18000);
	animlinear->add_Animation(std::move(animcombine));
	animlinear->add_Animation(std::move(anim3));

	add_animation(std::move(animlinear), "entering");
	play_animation("entering");

	parchemin = std::move(create_parchemin(textureGestioner, sf::Vector2f{ SIZE_X / 6  , 256}));
}


std::shared_ptr<Parchemin> Character::create_parchemin(TextureGestioner &textureGestioner, sf::Vector2f position)
{
	auto parchemin = std::make_shared<Parchemin>(position, textureGestioner, 6);

	return parchemin;
}


void Character::_update(sf::RenderWindow &mWindow, const float &deltaSec)
{

	if (Timer_get_in == 0) 
	{
		parchemin->update(mWindow, deltaSec);
	}
	else
	{
		Timer_get_in = std::max(Timer_get_in - deltaSec,0.f);
		if (Timer_get_in == 0)
		{
			parchemin->set_position(position + get_size() / 2.f);
			parchemin->activate_parchemin();
		}
	}
}

std::shared_ptr<Parchemin> Character::get_parchemin() const
{
	return parchemin;
}