
#include "Parchemin.h"


Parchemin::Parchemin(const sf::Vector2f &position, TextureGestioner &textureGestioner)
: InteractibleObject(position, textureGestioner.load(Textures::Parchemin, "resources/parchemin.png"), sf::Vector2f(2, 2))
{
}
