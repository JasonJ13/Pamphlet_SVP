
#include "ParcheminLittle.h"

#include "Interface/InterfaceSprite.h"
#include "../Animation/AnimationUnit.hpp"
#include "../Animation/AnimationGroupParallel.h"

ParcheminLittle::ParcheminLittle(const sf::Vector2f &position, TextureGestioner &textureGestioner) : InteractibleObject{ std::make_unique<InterfaceSprite>("Resources/parchemin.png", textureGestioner, 5, 0.02) }
{
	set_position(position);
	auto throwAnim = std::make_unique<AnimationUnit<float>>(&this->position.y, this->position.y + 256, 0.2);
	add_animation(std::move(throwAnim), "throw");
	play_animation("throw");

	auto shakeAnim = std::make_unique<AnimationUnit<sf::Angle>>(&angle, sf::degrees(5), 0.1, true, true);
	auto zoomAnim = std::make_unique<AnimationUnit<sf::Vector2f>>(&size, size + sf::Vector2f(0.1, 0.1), 0.1);

	auto grabAnim = std::make_unique<AnimationGroupParallel>(0.4);
	grabAnim->add_Animation(std::move(shakeAnim));
	grabAnim->add_Animation(std::move(zoomAnim));

	add_animation(std::move(grabAnim), "grab");

	auto dezoomAnim = std::make_unique<AnimationUnit<sf::Vector2f>>(&size, size - sf::Vector2f(0.1, 0.1), 0.1);
	add_animation(std::move(dezoomAnim), "release");
}



void ParcheminLittle::_grabed(const sf::Vector2i &mouse_position)
{
	play_animation("grab");
}
void ParcheminLittle::_hold(const sf::Vector2i &mouse_position)
{

}
void ParcheminLittle::_release(const sf::Vector2i &mouse_position, const sf::Vector2f &last_position)
{
	play_animation("release");
}

void ParcheminLittle::_update(sf::RenderWindow &mWindow, const float &deltaSec)
{

}