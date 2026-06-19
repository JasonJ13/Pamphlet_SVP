
#include "Character.h"

#include <memory>
#include <utility>

#include "../Animation/AnimationUnit.hpp"
#include "../Animation/AnimationGroupLinear.h"
#include "../Animation/AnimationGroupparallel.h"


Character::Character(sf::Vector2f position, TextureGestioner &textureGestioner) : GameObject{ position, textureGestioner.load(Textures::Cyrano,"Resources/Cyrano.png"), sf::Vector2f(8,8) }
{
	auto anim1 = std::make_unique<AnimationUnit<float>>(&this->position.x, 320, 5);
	auto anim2 = std::make_unique<AnimationUnit<float>>(&this->position.y, this->position.y + 10, 0.25, true, true);

	auto animcombine = std::make_unique<AnimationGroupParallel>(5);
	animcombine->add_Animation(std::move(anim1));
	animcombine->add_Animation(std::move(anim2));

	auto anim3 = std::make_unique<AnimationUnit<float>>(&this->position.y, this->position.y + 10, 1, true, true);

	auto animlinear = std::make_unique<AnimationGroupLinear>(10);
	animlinear->add_Animation(std::move(animcombine));
	animlinear->add_Animation(std::move(anim3));

	add_animation(std::move(animlinear), "entering");
	play_animation("entering");
}
