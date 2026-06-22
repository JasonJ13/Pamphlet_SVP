
#include "InterfaceSprite.h"
#include "Interface.h"

#include "../../TextureGestioner.h"

InterfaceSprite::InterfaceSprite(const std::string_view &file_name, TextureGestioner &texturegestioner, const int &priority, const float &scale) : Interface{priority}, sprite{texturegestioner.load(file_name)}
{
	set_size(scale);
}
InterfaceSprite::InterfaceSprite(const sf::Sprite &sprite, const int &priority) : sprite{sprite}, Interface{priority} {}


sf::Vector2f InterfaceSprite::_get_position() const { return sprite.getPosition(); }
sf::Angle InterfaceSprite::_get_angle() const { return sprite.getRotation(); }
sf::Vector2f InterfaceSprite::_get_size() const 
{ 
	sf::Vector2u texture_size = sprite.getTexture().getSize();
	sf::Vector2f Sprite_scale = sprite.getScale();
	return sf::Vector2f{ Sprite_scale.x * texture_size.x,Sprite_scale.y * texture_size.y};
}

void InterfaceSprite::_set_position(const sf::Vector2f &position) { sprite.setPosition(position); }
void InterfaceSprite::_set_angle(const sf::Angle &angle) { sprite.setRotation(angle); }
void InterfaceSprite::_set_size(const sf::Vector2f &size) { sprite.setScale(size); }


void InterfaceSprite::_display(sf::RenderWindow &window) const
{
	window.draw(sprite);
}