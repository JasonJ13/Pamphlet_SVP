
#include "FixObject.h"

#include "Interface/Interface.h"

FixObject::FixObject(const float &x, const float &y, const std::string_view &sprite_name, TextureGestioner& textureGestioner, const sf::Vector2f &size, const int &priority) : GameObject{ x, y, textureGestioner.load(sprite_name), size, priority } {}
FixObject::FixObject(const sf::Vector2f &position, const std::string_view &sprite_name, TextureGestioner& textureGestioner, const sf::Vector2f &size, const int &priority) : GameObject{ position, textureGestioner.load(sprite_name), size, priority } {}

FixObject::FixObject(std::unique_ptr<Interface> &&interface) : GameObject{std::move(interface)} {}

void FixObject::_update(sf::RenderWindow &mWindow, const float &deltaSec) {}
