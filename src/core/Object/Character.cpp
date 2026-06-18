
#include "Character.h"



Character::Character(sf::Vector2f position, TextureGestioner &textureGestioner) : GameObject{ position, textureGestioner.load(Textures::Cyrano,"Resources/Cyrano.png"), sf::Vector2f(8,8) }
{
	create_animation_position_x(320, 5, "walking", true);
	create_animation_position_y(position.y + 10, 0.2, "breathing", true, true, true);
}